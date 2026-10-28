    public static List<Integer> bfs(int n, int m, List<List<Integer>> edges, int s) {
        Map<Integer, Set<Integer>> emap = new HashMap<>();
        for (List<Integer> edge : edges) {
            int from = edge.get(0) - 1;
            int to = edge.get(1) - 1;
            emap
                .computeIfAbsent(from, (ign) -> new LinkedHashSet<Integer>())
                .add(to);
            emap
                .computeIfAbsent(to, (ign) -> new LinkedHashSet<Integer>())
                .add(from);
        }
        
        List<Integer> dists = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            dists.add(-1);
        }
        dists.set(s - 1, 0);
                
        LinkedList<Integer> queue = new LinkedList<>();
        queue.addLast(s - 1);
        while (!queue.isEmpty()) {
            int u = queue.removeFirst();
            
            for (int v : emap.getOrDefault(u, Set.of())) {
                if (dists.get(v) == -1) {
                    dists.set(v, dists.get(u) + 1 + 5);
                    queue.addLast(v);
                }
            }
        }
        
        dists.remove(s - 1);
        return dists;
    }

