    public static List<Integer> getTopKFrequentEvents(List<Integer> events, int k) {
        HashMap<Integer, Integer> histogram = new HashMap<>();
        HashMap<Integer, Integer> insertOrder = new HashMap<>();
        
        for (int i = 0; i < events.size(); i++) {
            int evt = events.get(i);
            histogram.put(evt, 1 + histogram.getOrDefault(evt, 0));
            insertOrder.putIfAbsent(evt, i);
        }

        return histogram
            .entrySet()
            .stream()
            .sorted((a, b) -> {
                int comp = b.getValue().compareTo(a.getValue());
                if (comp != 0) return comp;
                return insertOrder.get(a.getKey()).compareTo(insertOrder.get(b.getKey()));
            })
            .map(e -> e.getKey())
            .limit(k)
            .collect(Collectors.toList());
    }

