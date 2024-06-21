# Function to add two numbers
def add(x, y): @{
    return x + y
@}

# Function to subtract two numbers
def subtract(x, y): @{
    return x - y
@}

# Function to multiply two numbers
def multiply(x, y): @{
    return x * y
@}

# Function to divide two numbers
def divide(x, y): @{
    if y == 0: @{
        return -1
    @}
    return x / y
@}

x = 10
y = 5


x = add(x, y)



