    public static long countSubarraysWithSumAndMaxAtMost(List<Integer> nums, long k, long M) {
        HashMap<Long, Long> histo = new HashMap<>();
        
        long count = 0;
        long sum = 0;
        
        histo.put(0L, 1L);
        for (int n : nums) {
            if (n > M) {
                sum = 0;
                histo.clear();
                histo.put(0L, 1L);
                continue;
            }
            
            sum += n;
            
            long d = sum - k;
            if (histo.containsKey(d)) {
                count += histo.get(d);
            }
            histo.put(sum, histo.getOrDefault(sum, 0L) + 1);
        }
        
        return count;
    }

