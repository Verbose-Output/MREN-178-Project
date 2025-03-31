# MREN-178-Project
Data structures algorithms class project. Queens 2025 :)

To use the project as intended, two pieces of software are required. The Arduino IDE (which you should have already) and the Processing IDE. The Processing IDE is necessary to run the graphical portion of the project. 

## Installation of Processing IDE:

Step 1. Downloading
Visit https://processing.org/download and click the blue download button. It should display something along the lines of “Download Processing 4.3.4 (or a later version) for Windows.”

## Step 2. File Extraction
The download should be a .zip folder, extract this folder to the destination of your choosing.

## Step 3. Opening the IDE
Once extracted, open the folder and double-click the processing application (it should display a blue processing logo). This will open the IDE. When doing this for the first time, you may be prompted by Windows not to run the application. If this happens, click on “details” and then proceed with running anyway. This is how you will open the IDE as we advance (it is unlikely that you will encounter the Windows firewall issue again).

## Step 4. IDE Familiarization
The Processing IDE is very similar to the Arduino IDE, and its navigation is also very similar. No libraries or other plugins are required in the IDE for the project to run as intended.

## Step 5. Getting the Environment ready to run
To run the graphics code, copy and paste the entire contents of the file with the .pde extension into the Processing IDE.

## Step 6. Running the code!
After completing step 5 and uploading the Arduino code to the Uno board, run the processing sketch (hit the play button). This should output some information in the terminal about the available serial ports to make the program work as intended, change the index of the setup function to match the COM port the Arduino is connected to. Once this is completed, to run the program from now on, simply run the processing sketch; do not open the serial monitor in the Arduino IDE, as this blocks serial communication between the Processing IDE and the Arduino. It is recommended that you reset the Arduino between each use of the project and allocate a short period of time (<1minute) between trials to avoid serial connection issues between the processing sketch and the Arduino.

## Step 7. Enjoy 😊 
Once all the code is running, the servo may exhibit initially erratic behaviour; this is due to the Arduino disconnecting and reconnecting to the computer’s serial communication. Please allow at least 3 cycles of the servo’s rotation to complete before placing objects in front of the radar. Ensure that the servo is placed in an area that is open without obstacles that are not of interest to avoid confusion. The servo motor and ultrasonic sensor will not begin to operate until the processing sketch is started.


## Bonus:
By default, the processing sketch traces objects with a series of points; there is another operating mode that calculates the center of the object and only places a point at that location. To switch between these operating modes, comment or uncomment the matching section in the “drawObject” function in the processing sketch. Should you decide to use the middle point mode, be sure also to uncomment the “updateObjectFading” function call in the “draw” function, to clear the dots in middle point mode, simply press “c” on your keyboard.