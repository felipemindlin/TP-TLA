
x = 10
y = 5
# Function to add two numbers
def add(x_add, y_add): @{
    return x_add + y_add
@}

# Function to subtract two numbers
def subtract(x_sub, y_sub): @{
    return x_sub - y_sub
@}

# Function to multiply two numbers
def multiply(x_mul, y_mul): @{
    return x_mul * y_mul
@}

# Function to divide two numbers
def divide(x_div, y_div): @{
    if y_div == 0: @{
        return -1
    @}
    return x_div / y_div
@}


a = add(x, y)
s= subtract(x, y)
m = multiply(x, y)
d = divide(x, y)



