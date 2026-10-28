    private final static TreeSet<Integer> EMPTY_SET = new TreeSet<>();
    public static List<Integer> icecreamParlor(int m, List<Integer> arr) {
        HashMap<Integer, Set<Integer>> costToFlavour = new HashMap<>();
        for (int i = 0; i < arr.size(); i++) {
            costToFlavour
                .computeIfAbsent(arr.get(i), (ign) -> new TreeSet<>())
                .add(i + 1);
        }
        for (int i = 0; i < arr.size(); i++) {
            int rem = m - arr.get(i);
            final int flavour_i = i + 1;
            
            Optional<Integer> other = costToFlavour
                .getOrDefault(rem, EMPTY_SET)
                .stream()
                .filter(flavour -> flavour != flavour_i)
                .findFirst();
            if (other.isPresent()) {
                int a = flavour_i;
                int b = other.get();
                return List.of(
                    a > b ? b : a,
                    a > b ? a : b);
            }
        }
        return List.of();
    }

