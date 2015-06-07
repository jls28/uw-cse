'''
Created on Feb 28, 2013

@author: Stefan
'''
colors = ['red', 'blue', 'green']

print(colors)
sum = 0
for i in range(100):
    sum += i
print(sum)
sum = 0
numbers = [1, 3, 5, 6, 7, 5, 6, 7, 9, 0, 1, 2, 6, 7, 4]
for i in numbers:
    print(i)
    
    sum += i
    
    print('sum is: ' + str(sum))
print(sum)

i = 0
while i < len(numbers):
    print(str(i) + 'th place: ' + str(numbers[i]))
    i += i+1
friends = ['john', 'ian', 'justin', 'joe', 'whore', 'simon']
#make new list of reversed
i = len(friends)
friendsreversed = []
while i > 0:
    friendsreversed.append(friends[i - 1])
    i -= 1
print(friendsreversed)
#make friends reversed with no new objects
