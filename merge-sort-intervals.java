    private static int compare(List<Integer> a, List<Integer> b) {
        int ab = a.get(0) - b.get(0);
        if (ab != 0) return ab;
        return a.get(1) - b.get(1);
    }

    public static List<List<Integer>> mergeHighDefinitionIntervals(List<List<Integer>> intervals) {
        LinkedList<List<Integer>> result = new LinkedList<>();

        List<List<Integer>> sorted = intervals
            .stream()
            .sorted((a, b) -> compare(a, b))
            .collect(Collectors.toList());
        
        for (List<Integer> i : sorted) {
            if (result.isEmpty()) {
                result.add(i);
                continue;
            }
            List<Integer> last = result.peekLast();
            if (last.get(1) >= i.get(0)) {
                last.set(1, Integer.max(last.get(1), i.get(1)));
            } else {
                result.add(i);
            }
        }
            
        return result;
    }

