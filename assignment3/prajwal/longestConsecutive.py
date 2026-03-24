class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        sortedNums = sorted(nums)

        if nums == []:
            return 0
        print(f"Sorted List : {sortedNums}")
        # finding longest consecutive..
        streak = 1 # to keep track of the streak of consecutive nums
        maxStreak = 1

        for i in range(1, len(sortedNums)):

            if ( sortedNums[i] == sortedNums[i-1] ): # for duplicates
                continue

            if ( sortedNums[i] == sortedNums[i-1]+1 ):
                streak+=1
            else: 
                maxStreak = max(maxStreak , streak)
                streak = 1
        
        return max(maxStreak, streak)

foo = Solution()
numList = [0,1,5,6,7,8,9,10,11,462,2673,247,475,6851,35,74]
print(f"number of digits in the sequence : {foo.longestConsecutive( numList )}")
