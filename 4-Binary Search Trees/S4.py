#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Algo-4-Huffman.py: 
   Solution sketch for Algorithm Assignment 4 on Huffman Coding.
   Steps for the algo is explained in comments
"""

__author__      = "Bishal Santra"

import random
from collections import Counter

## Read the log file and split the text in file by characters ->
## Store this data in array s of characters
s = ''.join([l.strip().lower() for l in open('log.txt').readlines()[1:]])

## Count the occurrence of different characters
_chars = Counter(s)
print(_chars)

## We are only considering alphanumeric characters.
## alphnum: A list containing a-z and 0-9
alph = list(map(chr, range(ord('a'), ord('z')+1)))
nums = list(map(chr, range(ord('0'), ord('9')+1)))
alphnum = alph + nums

## Build the dictionary of {c: freq_of_c}
## c: any alphanumeric character
## freq_of_c >= 0 (0 for unseen characters)
CC = {d:_chars[d] if d in _chars else 0 for d in alphnum}
print("CC:", CC)
# H = huffman.codebook(CC.items())

## Print Frequencies to output file
with open("output.txt", 'w') as f:
    f.write(",".join([f"{d}={CC[d]}" for d in alphnum]) + "\n")
    # print(H)

## Node for Huffman tree with Conflict resolution scheme
class Node:
    def __init__(self, symbol, freq=None, left=None, right=None):
        """
        Constructs all the necessary attributes for each node in the Huffman Tree.
        These nodes are used to create the initial linked list which is later converted 
        into a Huffman Tree using the steps as described in assignment 4 pdf.

        Parameters
        ----------
            symbol: the character
            freq: frequency of the character in text
                or the total frequency for a supernode
            left : Left child of this node
            right: Right child of this node
        """
        self.symbol = symbol
        if left is None:
            # Normal frequency for a character
            self._freq = freq
        else:
            # Sum of frequencies of children in case of a supernode
            self._freq = left._freq + right._freq
        self.left = left
        self.right = right
        
        """atomicW_:
        atomicW_ is added to frequency to resolve conflicts due to
        equal frequencies.
        
        atomicW_ (a <= c <=  z): 0.5 + .001*(ASCII of char c)
        atomicW_ (0 <= c <=  9): 0.7 + .001*(ASCII of char c)
        atomicW_ (Supernode Ni, i>=1): .001*(i)
        """
        self.atomicW_ = 0.0
        delta = 1/1000 # 0.001: Total number of nodes will definitely be less than 1000
        if self.symbol[0] >= "a" and self.symbol[0] <= "z":
            self.atomicW_ = delta*(500 + ord(self.symbol) - ord("a"))
        elif self.symbol[0] >= "0" and self.symbol[0] <= "9":
            self.atomicW_ = delta*(int(self.symbol) + 700) # 950 for N, 26 for a-z
        else:
            self.atomicW_ = delta*int(self.symbol[1:])

        # Sum of actual frequency of character and the atomicW_
        self.freq = self._freq + self.atomicW_

    def __str__(self):
        # return f"({self.symbol}, {self.freq + self.atomicW_:0.3F})"
        return f"({self.symbol}, {self._freq}, {self.atomicW_:0.3F})"

    def __repr__(self):
        return self.__str__()

# Create the linked list with initial nodes for characters.
linked_list = [Node(c, freq=freq) for c, freq in CC.items()]

def ysort(L):
    """
    Sorts the main linked list. 
    The function sorted should implement any sorting method.
    The best (easiest to implement) choice of sorting for this problem
    is insertion sort. But any implementation of sorting is equally valid.
    """
    return sorted(L, key=lambda x: x.freq)

# Sort the linked list.
linked_list = ysort(linked_list) # Sort in increasing order
print(linked_list)

# Creating the Huffman Tree
i = 1 # Starting supernode id
while(len(linked_list) > 1):
    # Nodes with lowest frequencies
    a = linked_list[0]
    b = linked_list[1]
    if a.freq < b.freq:
        left, right = a, b
    elif a.freq > b.freq:
        left, right = b, a
    else:
        # Just a sanity check. With atomicW_ we shouldn't 
        # encounter any pair of nodes with equal count.
        raise Exception("THIS SHOULDNT HAPPEN!")

    # Create supernode
    sn = Node(f"N{i}", left=left, right=right)
    i+=1
    linked_list = [sn] + linked_list[2:]

    # Sort again to position new supernode correctly.
    linked_list = ysort(linked_list) # Sort in increasing order
    print(f"{len(linked_list)}... {left.symbol} << {sn.symbol} >> {right.symbol}\t\t{left} << {sn} >> {right}")

# After the while loop finishes you will have the Huffman Tree ready. Root will be linked_list[0].

pre_order_string = []
H2 = {}
def traverse(T, code=""):
    print(T, code)
    pre_order_string.append(f"{T.symbol}({T._freq})")
    if T.left is None:
        H2[T.symbol] = code
        return
        # print(T.symbol, end = " ")
    else:
        traverse(T.left, code+"0")
        traverse(T.right, code+"1")

traverse(linked_list[0])
print()
with open("output.txt", 'a') as f:
    print(",".join(pre_order_string))
    f.write(",".join(pre_order_string) + "\n")

    for d in alphnum:
        f.write(f"{d} {H2[d]}\n")

# for c in H:
#     print(c, H[c], H2[c])
    # assert(H[c] == H2[c])


#################################################################################
## Encode.txt
coder = H2
def encode(word):
    em = ""
    for w in word:
        em += coder[w]
    return em

with open('encode.txt') as f, open('output.txt', 'a') as wf:
    for i,l in enumerate(f):
        if i == 0:
            # skip first line
            continue
        l = l.strip()
        if len(l) > 0:
            wf.write(encode(l) + '\n')

## Decode.txt
decoder = {c:w for w, c in coder.items()}
def decode(em):
    # em = em.split("")
    cache = []
    result = []
    for c in em:
        cache.append(c)
        _t = ''.join(cache)
        if _t in decoder:
            result.append(decoder[_t])
            cache = []
    return ''.join(result)

with open('decode.txt') as f, open('output.txt', 'a') as wf:
    for i,l in enumerate(f):
        if i == 0:
            # skip first line
            continue
        em = l.strip()
        wf.write(decode(em) + '\n')
###########################################################################
