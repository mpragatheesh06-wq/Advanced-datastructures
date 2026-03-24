import random

class Solution:
	def longestConsecutive(self, nums: list[int]) -> int:
		numSet = set(nums)	# convert to a list

		if not numSet: # if the list was empty 
			return 0

		streak = 1	# to keep track of the current streak (when a list with single element is used - one number can form a sequence of 1 element)
		maxStreak = 1


		for num in numSet:
			if num -1 not in numSet:		# when if the previous number isn't in the list => that means the number could be a the first number of a sequence
				currentNum = num 
				while currentNum+1 in numSet:	# continue this loop until no consecutive number is in the set
					streak+=1
					maxStreak = streak if streak >= maxStreak else maxStreak
					currentNum +=1
				streak = 1	# resets the set back to 1

		return max( maxStreak , streak)


def generateARandomList(size: int , maxRange: int) -> list:
	newList = []

	for _ in range(size):
		newList.append(random.randint(0,maxRange))
	return newList

solve = Solution()

#  Tweak these variables to generate new cases
numberOfElements = 200 # the number of elements you want in the list
upto = 100 # the upperbound of numbers to be generated

newList = generateARandomList(numberOfElements , upto)

print( f"The generated List (without duplicates): {set(sorted(newList))}") # Prints the generated random List 

												# change this to pass a custom List
print(f"\n\nNumber of digits Longest sequence = {solve.longestConsecutive(newList)} ")