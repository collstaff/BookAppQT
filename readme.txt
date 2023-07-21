BookStore Application

Final version by Collin Stafford, Noah Vanderveen, and Leydi Martinez

The purpose of this application is to provide a book store application that allows the user to save, purchase, and add books 
to and from an inventory system. This was made in QT Creator so the application would have a functioning GUI. I have written all of the SQL statements to connect to a local database. This was a group project, and I cannot
take credit for the logging system, that was solely done by Noah. 
Features
Search for books
Through the “Search” tab, the user is able to search for any books that closely match to a book title in the database
Add to book list, save list, and export list to text file
Through the “Book List” tab, the user is able to search for books, then add the search results to a list. After doing so, the user is able to save the list to the database in the LISTS table. 
The user is able to click a button to export the list to a text file. The name of this text file is named “BookList.txt”
Add books to a shopping cart, then purchase the books in the list
Through the “Book List” tab, the user is able to search for books, then add the search results to a shopping cart. After doing so, the user can then navigate to the “Shopping Cart” tab. The user must enter a name and email address, then click the “Purchase Books” button.
The order is saved into the “SHOPPERS” database table
The app will take the books in the shopping list, and reduce their quantity value by 1, simulating an actual purchase and removal of that book from the inventory.
Splash Screen
If the user has a second monitor, a simple splash screen will appear on that monitor and take up 15% of the screen.
Log file
The log file in question is named “BookStoreLogs.txt”
A log class was created and contains methods to open the file, close the file, and log an item, using QString as an argument. This class is used throughout the program to populate the log file.
Login
The user is able to log in using a username and password. Access to the app is not allowed unless there is a successful login
Hardware information
By selecting “Help -> Hardware Information” in the menu bar, the user is able to view their hardware
Status bar
The status bar gives single line updates on operations, such as searches, list saving, and purchases.
Notes
By selecting “File -> Notes” in the menu bar, the user is able to enter notes into a text box and export those notes to a text file.
The name of the text file is “BookStoreNotes.txt”
Remove User (In admin menu)
The user is able to use an alternate font, if they so choose, by clicking a checkbox and selecting an “Apply” button in a dialog that is accessed through the menu bar.
The user will be able to toggle the font weight to bold throughout the entire application.

