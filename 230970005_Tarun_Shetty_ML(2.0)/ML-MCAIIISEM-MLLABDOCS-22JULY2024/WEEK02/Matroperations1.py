#!/usr/bin/env python
# coding: utf-8

# In[1]:


row1 = int(input("Row of Matrix1: "))
col1 = int(input("Column of Matrix1: "))
row2= int(input("Row od Matrix2: "))
col2= int(input("Column of Matrix2: "))


# In[2]:


matrix1 =[]
matrix2 =[]


# In[3]:


print("Elements of Matrix 1")
for i in range(row1):
    a=[]
    for j in range(col1):
        a.append(int(input()))
    matrix1.append(a)

#to print the array in matrix format

for i in range (row1):
    for j in range (col1):
        print(matrix1[i][j], end=" ")
    print()


# In[4]:


print("Elements of Matrix 2")
for i in range(row2):
    a=[]
    for j in range(col2):
        a.append(int(input()))
    matrix2.append(a)

#to print the array in matrix format

for i in range (row2):
    for j in range (col2):
        print(matrix2[i][j], end=" ")
    print()


# In[5]:


for i in range(row1):
    for j in range(col1):
        print(matrix1[i][j] , end=" ")
    print()


# In[6]:


for i in range(row2):
    for j in range(col2):
        print(matrix2[i][j] , end=" ")
    print()


# In[11]:


add = [[0,0,0],
         [0,0,0],
         [0,0,0]]
print("Addition of two matrices")
for i in range(row1):
    for j in range(col1):
        add[i][j] = matrix1[i][j] + matrix2[i][j] 

for r in add:
    print(r)


# In[ ]:




