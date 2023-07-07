def main():
    height = get_height()  # Call the get_height function to get the desired height
    print_pyramid(height)  # Call the print_pyramid function to print the pyramid

def get_height():
    while True:
        try:
            n = int(input("Height: "))  # Prompt the user to enter the desired height and convert it to an integer
            if 1 <= n <= 8:  # Check if the entered value is within the valid range of 1 to 8
                return n  # If it is, return the valid height
            else:
                # If the entered value is not within the valid range, display an error message
                print("Height should be between 1 and 8.")
        except ValueError:
            # If the entered value is not a valid integer, display an error message
            print("Invalid input. Please enter a positive integer.")

def print_pyramid(height):
    for i in range(1, height + 1):  # Iterate from 1 to the given height (inclusive)
        # Calculate the number of spaces based on the difference between the total height and the current row number
        spaces = " " * (height - i)
        blocks = "#" * i  # Create a string of '#' symbols based on the current row number
        print(spaces + blocks)  # Print the concatenation of spaces and blocks to create the pyramid structure

main()  # Call the main function to start the program execution
