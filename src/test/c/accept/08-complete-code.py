

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
    return x_div / y_div
   
@}

def orFunc(x_or, y_or)@{
    return x_or or y_or    
@}

def andFunc(x_and, y_and)@{
    return x_and and y_and    
@}

x = 10.4
y = 5
hola="Hola Mundo"
dec = 10.5
a = add(x, y)
s= subtract(x, y)
m = multiply(x, y)
d = divide(x, y)
tru = True
fal = False
my_or = orFunc(tru,fal)
my_and = andFunc(tru,fal)

