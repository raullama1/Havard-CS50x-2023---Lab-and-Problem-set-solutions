from cs50 import get_string

def main():
    text = get_string("Text: ")  # Prompt the user to enter the text
    letters = count_letters(text)  # Count the number of letters in the text
    words = count_words(text)  # Count the number of words in the text
    sentences = count_sentences(text)  # Count the number of sentences in the text
    grade_level = calculate_grade_level(letters, words, sentences)  # Calculate the grade level
    print_grade(grade_level)  # Print the grade level

def count_letters(text):
    letters = sum(1 for char in text if char.isalpha())  # Count each character that is an alphabet letter
    return letters

def count_words(text):
    words = len(text.split())  # Split the text into words and count the number of resulting elements
    return words

def count_sentences(text):
    sentences = sum(1 for char in text if char in ['.', '!', '?'])  # Count each character that indicates the end of a sentence
    return sentences

def calculate_grade_level(letters, words, sentences):
    L = (letters / words) * 100  # Calculate the average number of letters per 100 words
    S = (sentences / words) * 100  # Calculate the average number of sentences per 100 words
    index = 0.0588 * L - 0.296 * S - 15.8  # Calculate the Coleman-Liau index
    return round(index)

def print_grade(grade_level):
    if grade_level < 1:
        print("Before Grade 1")  # Print the grade level as "Before Grade 1" if it is less than 1
    elif grade_level >= 16:
        print("Grade 16+")  # Print the grade level as "Grade 16+" if it is 16 or higher
    else:
        print(f"Grade {grade_level}")  # Print the grade level in the format "Grade X" where X is the calculated grade level

if __name__ == "__main__":
    main()
