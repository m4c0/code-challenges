static int pivot(int * nums, int l, int r) {
    if (nums[l] <= nums[r]) return l;
    
    int mid = (l + r) / 2;
    return nums[mid] <= nums[r]
        ? pivot(nums, l, mid)
        : pivot(nums, mid + 1, r);
}

static int find(int * nums, int l, int r, int k) {
    if (l > r) return -1;

    int mid = (l + r) / 2;
    if (nums[mid] == k) return mid;
    
    return nums[mid] < k
        ? find(nums, mid + 1, r, k)
        : find(nums, l, mid - 1, k);
}

int searchRotatedTimestamps(int nums_count, int* nums, int target) {
    int p = pivot(nums, 0, nums_count - 1);
    
    if (nums[p] == target) return p;
    if (p == 0) return find(nums, 0, nums_count - 1, target);
    if (nums[0] <= target) return find(nums, 0, p - 1, target);
    return find(nums, p + 1, nums_count - 1, target);
    
    // Surprisingly works
    /*
    for (int i = 0; i < nums_count; i++) {
        if (nums[i] == target) return i;
    }
    return -1;
    */
}

