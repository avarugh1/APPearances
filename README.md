# APPearances
By Anson Varughese

## Description
APPearances is a C++ program which analzyes a given Android app against a database of 10000 mobile apps. From this analysis, we can see the app which has received the highest revenue and the app which receives the closest revenue to the given app. From this data, we can predict the leading company in this space and the closest competitor to our given app.

## Inspiration
By browsing different datasets, the 10000 Play Store App data caught my eye. It was then that I realized that predictive analysis could be made on any app that is currently being built. Who is my closest competitor in this category? How much are they making? What download targets and price point do I have to reach to match them or surpass them? Who is leading the same category in revenue? These are all questions that can be answered with this application

## Directions to run
$ make

$ ./APPearances

## Technical Details
C++11, File Manipulation, Kaggle, Make 

The program is separated into the driver, the CSV parser, and the Analyzer. 
