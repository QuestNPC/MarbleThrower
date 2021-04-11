## Learning diary
### Summary of the idea:

Our idea is to make a device for throwing marbles. Initial concept was a catapult that was operated by servo, had ability to rotate, and responded to the distance of the target.

### Week 12

This week was mostly discussing and developing our idea for throwing marbles. Wednesday was our first discussion with whole group where we brainstormed what is presented in the introductory report.
On Friday we discussed the idea during the TA session and we got confirmation on our worries that servo might not be able to operate the arm well enough by itself. Also TA reminded us to focus on figuring out how we will impement the throwing before working on other functionalities. TA mentioned the trebuchet that was made few years back, however trebuchet uses counterweight to swing and the students used servo to pull the rope that pulled the arm back.

After the TA session we discussed the idea futher, this time exploring using springs to move the arm and sevro to tension it, we had a passing mention of this during discussion on wednesday and that was decided as possible back up if TA session confirmed servo insufficent. Discussing and researching implementations made by other people in the internet we updated the arm to be held down with a lever operated with servo, while another servo tensions the arm by rotating another arm that has a rubberband connected to the throwing arm. 

<img src="images/update1.png" width="800">

Rough sketch of the updated idea.


### Week 13

This week we started to actually work on the project. As the priority number one we started making a 3d model of the project after fiddling around with Autodesk Fusion 360, which is our software of choice for the project. What we managed to make was a basic structure of our throwing machine. What needs to be made is to modify the structure to fit the components. While working on the model trying to animate joints to simulate the throwing motion proved to be challenging. After some fumbling around some insight on how it works in Autodesk Fusion 360 was gained. However, satisfactory results are yet to be found, proving there is learning to do. 
<img src="images/some_3d_modeling.png" width="800">

Antti also picked up circuit design and code using Tinkercad as the platform. So far he has managed to implement 2 servos to roate in response to a button press. Later on third servo and potentiometer added to make rotation possible.  

<img src="images/Circuit_design.png" width="1000">

First version of circuit design and code.

### Week 14 

We finally recived our components for this project so it was time to build ciruit and test it in real life rather than in simulation. The circuit worked great on arduino as was expected. We had some concerns about the amount of torque a simple servo motor can provide so we made this test arm for the loading servo out of cardboard and tape. In the end of the loading arm there is two rubber bands that are tied together. After running some tests with this setup we can roughly say that the amount of torque the servo motor can provide isn't much. We already had some ideas on how to solve this problem if it becomes an issue. One solution would be to use cogwheels with the servo to decrease its range of motion but increase the torque the servo provides. 

<img src="images/Arduin_circuitV1.jpg" width="600">

Here is the arduino circuit with loading servo, release servo and the servo for rotating the catapult. The button on the breadboard controls the release and loading mechanism while the potentiometer is used to rotate the base of the catapult between 0 and 180 degrees.

Some progress also with circuit design and coding. Ultrasonic sensor and leds installed to the system. Depending of distance: one, two or three leds are on. 

<img src="images/Circuit_design_v2.png" width="1000">

Circuit design v2

<iframe src="images/Code_v2.txt" width="100%" height="300">

