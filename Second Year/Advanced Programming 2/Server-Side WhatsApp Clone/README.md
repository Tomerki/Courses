The installtions required for the project:
1. MARIA-DB for database. 
2. To link the DB to the Whats_App_ServerSide project, open the Package manager console and execute the add-migration init command and then update-database. 
3. Section 2 must also be performed for Whatsapp_Rating project. 
4. In a react project, one must perform:
     - npm install axios 
     - npm install @microsoft/signalr 
 
Note - in order to run the program, the server located at localhost:7288 must be run simultaneously along with the react project that located at localhost:3000. 
Also, to run the rating page that found at localhost:7215 you must set the project as startup project and only then run it. 
Which means we have three separate windows for the three parts of the program. 
 
In the Repo where we submitted the first exercise (called Whatsapp_Clone_Project) is also containing a brunch with the react code of this exercise, but to differentiate between the two of them,
The first exercise is at Brunch Master and the second exercise is in EX2_BRUNCH. 
 
the server side is in a separate Repo. (called Whats_App_ServerSide).
