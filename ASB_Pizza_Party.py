# ASB Pizza Party Night
# Alexander Potiagalov (301586871)
# Oct 6th, 2023

# Menu Lists (Items & Prices)
pizza_menu = ["veggie - $1.99",
              "meat - $1.99", 
              "hawaiian - $1.99", 
              "cheese - $1.99"
]
drink_menu = ["water - Free", 
              "coke-zero - $0.75", 
              "cranberry - $0.75", 
              "fanta - $0.75", 
              "sprite - $0.75"
]

# Menu List (Only Items) used for drink_choices and pizza_choices
drinks_list = ["water", "fanta", "cranberry", "sprite", "coke-zero"]
pizza_list = ["meat", "veggie", "hawaiian", "cheese"]

# Prices
pizza_price = 1.99
drink_price = 0.75

# Menu
print("Welcome to the ASB Pizza Party. Here is our menu.")
print("   DRINKS:")
for drink in drink_menu:
    print(drink)
print("   PIZZA:")
for pizza in pizza_menu:
    print(pizza)

# Drink Choices, Quantity and Price
print("Would you like a drink (yes/no)?")
drink_reply = input().lower().strip('!.').replace(" ", "")
if drink_reply == "yes":
    print("What drink would you like?")
    drink_choice = input().lower().strip('!.').replace(" ", "")
    if drink_choice in drinks_list:
        print("Sounds good! How many would you like?")
        drink_quantity = int(input().strip('!. '))
        if drink_quantity > 0:
            if drink_choice == 'water':
                order_price_drinks = 0
            else:
                order_price_drinks = drink_price * drink_quantity
            print("Got it,", drink_quantity , drink_choice + "(s).")
    else:
        print("Sorry, we don't have that here.")
        order_price_drinks = 0
else:
    print("Alright, no drinks.")
    order_price_drinks = 0

# Pizza Choices, Quantity and Price
print("And do you want pizza (yes/no)?")
pizza_reply = input().lower().strip('!.').replace(" ", "")
if pizza_reply == "yes":
    print("What pizza would you like?")
    pizza_choice = input().lower().strip('!.').replace(" ", "")
    if pizza_choice in pizza_list:
        print("Sounds good! How many would you like?")
        pizza_quantity = int(input().strip('!. '))
        if pizza_quantity > 0:
            print("Got it,", pizza_quantity , pizza_choice + "(s).")
            order_price_pizza = pizza_price * pizza_quantity 
    else:
        print("Sorry, we don't have that here.")
        order_price_pizza = 0
else:
    print("Alright, no pizza.")
    order_price_pizza = 0

# Total price with tax 
order_price = order_price_pizza + order_price_drinks
order_price_with_tax = order_price * 1.05
print("Your total with tax will be", '$' + format(order_price_with_tax, '.2f') + ".")
print("Thank you for coming. Enjoy!")
