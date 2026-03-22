HashMap<Integer, Integer> map = new HashMap<>();
int sum = 0;
int count = 0;

map.put(0, 1);

for (int i = 0; i < arr.length; i++) {
    sum += arr[i];

    if (map.containsKey(sum)) {
        count += map.get(sum);
    }

    map.put(sum, map.getOrDefault(sum, 0) + 1);
}