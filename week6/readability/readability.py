def main():
    text = input("Text: ") 
    sentense_end = ['.', '!', '?']
    word_dividers = [' ', '"', ',']
    letters = 0
    words = 0
    sentenses = 0
    in_word = False

    for character in text:
        if character in sentense_end:
            sentenses += 1
            if in_word:
                in_word = False
                words += 1
        elif character in word_dividers and in_word:
            in_word = False
            words += 1
        else:
            is_alpha = character.isalpha()
            if not in_word and is_alpha:
                in_word = True
            
            if is_alpha:
                letters += 1
    
    l = proportion_to_100(letters, words)
    s = proportion_to_100(sentenses, words)
    
    result = round(0.0588 * l - 0.296 * s - 15.8)
    final_result = int(result)

    if final_result < 1:
        print("Before Grade 1")
    elif final_result > 15:
        print("Grade 16+")
    else:
        print("Grade ", final_result)


def proportion_to_100(convertable, eqvivalent):
    return (convertable * 100) / float(eqvivalent)

main()