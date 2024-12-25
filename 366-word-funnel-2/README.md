[2018-08-22] Challenge #366 [Intermediate] Word funnel 2
=========================================================

<https://www.reddit.com/r/dailyprogrammer/comments/99d24u/20180822_challenge_366_intermediate_word_funnel_2/?st=jmr7busz&sh=001ba1d9>

## Challenge

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

## Optional bonus 1

Find the one word in the word list that starts a funnel of length 10.

## Optional bonus 2

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
