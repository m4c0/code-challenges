    // Partial. Still times out.

    public static long calculateMinimumSpanningTreeWeightWithFreeEdge(int n, int m, List<List<Integer>> edges) {
        if (n <= 1) return 0L;

        List<TreeSet<Integer>> cNodes = new ArrayList<TreeSet<Integer>>(n);
        int clusters[] = new int[n];
        for (int i = 0; i < n; i++) {
            clusters[i] = i;
            
            TreeSet<Integer> node = new TreeSet<>();
            node.add(i);
            cNodes.add(node);
        }
        
        List<List<Integer>> sorted = edges
            .stream()
            .sorted(Comparator.comparingInt(e -> e.get(2)))
            .collect(Collectors.toList());
        
        long sum = 0;
        int last = 0;
        for (List<Integer> e : sorted) {
            int cA = clusters[e.get(0)];
            int cB = clusters[e.get(1)];
            if (cA == cB) {
                continue; // cycle
            }
            
            TreeSet<Integer> nodeA = cNodes.get(cA);
            TreeSet<Integer> nodeB = cNodes.get(cB);
            
            nodeB
                .stream()
                .forEach(i -> {
                    nodeA.add(i);
                    clusters[i] = cA;
                });
            
            last = e.get(2);
            sum += last;
        }
                
        return sum - last;
    }

