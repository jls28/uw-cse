'''
Created on Feb 28, 2013

@author: Stefan
'''
print('hello world')
print(2**38)
print(4)
def repeat(s, exclaim):
    result = s + s + s
    if exclaim:
        result = result + 'fuck!'
    return result
def repeatO(s):
    return repeat(s, True)


print(repeat('i', True))

s = 'hi'
print (s + repeatO(' fag'))
pi = 3.14
print(pi)
print(pi + 4)
#print(pi + ' 4')
#print('pi' + 4)
print(str(pi) + ' 4')
multi = """ this is 
a 
buuuuuuuuuuuuuunch
of shiiiiiiiit
multiline as fuck"""
print(multi)
print(multi.upper())
print(multi.replace('i', 'a'))
