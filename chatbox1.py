#Alexander Potiagalov
#Sept 18th, 2023

#Question 1
print("Hey! I'm Drake the rapper.")
print("What's your name?")
name = input()
print("It's nice to meet you " + name +"!")

#If/elif/else *Question 2 
print("So how was your day?")
reply = input()
if reply == "good" or reply == "GOOD" or reply == "Good" or reply == "gooD" or reply == "GoOd": 
    print("That's great to hear.")

elif reply == "bad" or reply == "BAD" or reply == "BaD" or reply == "BAd" or reply == "bAD":
    print("That sucks to hear, I hope it gets better.")

else:
    print("Really! I feel the same way.")

#if/else *Question 3 
print("I got a quick question that I would like to ask you.") 
print('Have you listened to my most recent album, "Her Loss"?')
reply = input()

if reply == "yes" or reply == "YES" or reply == "Yes" or reply == "yeS" or reply == "YEs":
    print("Thank you for listening! It means a lot.")

else:
    print("Oh... Well I think you should, I recommend it.")

#if(without else) & or *Question 4 
print("Here's another question.")
print("On a scale from 1 to 5 how much do you like my music?")
reply = input()
if reply == "1" or reply == "2" or reply == "3" or reply == "4" or reply == "5":
    print("Thanks for your honesty, it means a lot.")

#Conclusion
print("Well my private jet is about to take off, I got to go now.")
print("Bye!")


