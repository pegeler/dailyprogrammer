Word Funnel
===========

## Installation

```r
if (!requireNamespace("remotes", quietly = TRUE)) install.packages("remotes")
remotes::install_github("pegeler/dailyprogrammer/366-word-funnel-r-pkg")
```

## [2018-08-20] Challenge #366 [Easy] Word funnel 1

<https://www.reddit.com/r/dailyprogrammer/comments/98ufvz/20180820_challenge_366_easy_word_funnel_1/?st=jmr7nnz4&sh=478ef928>

### Challenge

Given two strings of letters, determine whether the second can be made from the
first by removing one letter. The remaining letters must stay in the same
order.

Examples

    funnel("leave", "eave") => true
    funnel("reset", "rest") => true
    funnel("dragoon", "dragon") => true
    funnel("eave", "leave") => false
    funnel("sleet", "lets") => false
    funnel("skiff", "ski") => false

### Optional bonus 1

Given a string, find all words from the [`enable1` word
list](https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt)
that can be made by removing one letter from the string. If there are two
possible letters you can remove to make the same word, only count it once.
Ordering of the output words doesn't matter.

    bonus("dragoon") => ["dragon"]
    bonus("boats") => ["oats", "bats", "bots", "boas", "boat"]
    bonus("affidavit") => []

### Optional bonus 2

Given an input word from `enable1`, the largest number of words that can be
returned from `bonus(word)` is 5. One such input is `"boats"`. There are 28
such inputs in total. Find them all.

Ideally you can do this without comparing every word in the list to every other
word in the list. A good time is around a second. Possibly more or less,
depending on your language and platform of choice - Python will be slower and C
will be faster. The point is not to hit any specific run time, just to be much
faster than checking every pair of words.

## [2018-08-22] Challenge #366 [Intermediate] Word funnel 2

<https://www.reddit.com/r/dailyprogrammer/comments/99d24u/20180822_challenge_366_intermediate_word_funnel_2/?st=jmr7busz&sh=001ba1d9>

### Challenge

A word funnel is a series of words formed by removing one letter at a time
from a starting word, keeping the remaining letters in order. For the
purpose of this challenge, a word is defined as an entry in the [`enable1`
word
list](https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt).
An example of a word funnel is:
  
    gnash => gash => ash => ah

This word funnel has length 4, because there are 4 words in it.

Given a word, determine the length of the longest word funnel that it starts.
You may optionally also return the funnel itself (or any funnel tied for the
longest, in the case of a tie).

Examples

    funnel2("gnash") => 4
    funnel2("princesses") => 9
    funnel2("turntables") => 5
    funnel2("implosive") => 1
    funnel2("programmer") => 2

### Optional bonus 1

Find the one word in the word list that starts a funnel of length 10.

### Optional bonus 2

For this bonus, you are allowed to remove more than one letter in a single step
of the word funnel. For instance, you may step from *sideboard* to *sidebar* by
removing the *o* and the final *d* in a single step. With this modified rule,
it's possible to get a funnel of length 12:

    preformationists =>
    preformationist =>
    preformations =>
    reformations =>
    reformation =>
    formation =>
    oration =>
    ration =>
    ratio =>
    rato =>
    rat =>
    at

*preformationists* is one of six words that begin a modified funnel of length 12.
Find the other five words.
