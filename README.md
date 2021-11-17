# TourDeFrance, Description
Tour De France project is an introduction to manipulating large data sets. Tour de France is a bicycling
competition held in France. Like any international competition, racers are labeled by their individual name, 
team name, and country they're representing. In addition to this, we're also given a racer's "individual total 
race time" as well as their "classification" and "rider number". This sums to a total of six input
values. The program is designed to create output files with the organized data. It does NOT modify the data
in any shape or form. Outputed files organize data in different ways, depending on the type of file. There 
are three types of outputs: formatted, teams, country. More info on each output file can be found below in
the "Output Files" section. 


## Input Files
* "tdf20.in" ~ A file with raw data values. From left to right, the data values entered are: 

| Rider Number |   Racer Name |  Classification | Country Representing|  Team    |    Time      |
|      :--     |  :--         |    :--          |       :--           |  :--     |   :--        |
|    Ex, 128   |  Ex, Sanchez |  Ex, 46         |  Ex, Australia      |  Ex, AFU | Ex, 89:34:09 |

## Output Files
* "formatted.out" ~ Organizes the data based on classification. Adds a row stating each category and outputs
every data value with padding...so it looks nice :). Output values are in this order: Classification, Rider, 
Rider Number, Country, Team, Time(hh:mm:ss)
* "teams.out" ~ 
* "countires.out" ~ 
