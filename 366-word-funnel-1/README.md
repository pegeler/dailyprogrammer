[2018-08-20] Challenge #366 [Easy] Word funnel 1
================================================

<https://www.reddit.com/r/dailyprogrammer/comments/98ufvz/20180820_challenge_366_easy_word_funnel_1/?st=jmr7nnz4&sh=478ef928>

## Challenge

Given two strings of letters, determine whether the second can be made from the first by removing one letter. The remaining letters must stay in the same order.

Examples

    funnel("leave", "eave") => true
    funnel("reset", "rest") => true
    funnel("dragoon", "dragon") => true
    funnel("eave", "leave") => false
    funnel("sleet", "lets") => false
    funnel("skiff", "ski") => false

## Optional bonus 1

Given a string, find all words from the [`enable1` word list](https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt) that can be made by removing one letter from the string. If there are two possible letters you can remove to make the same word, only count it once. Ordering of the output words doesn't matter.

    bonus("dragoon") => ["dragon"]
    bonus("boats") => ["oats", "bats", "bots", "boas", "boat"]
    bonus("affidavit") => []

## Optional bonus 2

Given an input word from `enable1`, the largest number of words that can be returned from `bonus(word)` is 5. One such input is `"boats"`. There are 28 such inputs in total. Find them all.

Ideally you can do this without comparing every word in the list to every other word in the list. A good time is around a second. Possibly more or less, depending on your language and platform of choice - Python will be slower and C will be faster. The point is not to hit any specific run time, just to be much faster than checking every pair of words.
