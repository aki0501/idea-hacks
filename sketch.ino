#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid = "ESP32-Network";
const char* password = "your-password";

AsyncWebServer server(80);

void saveStringToFile(const String& data, const char* filename) {
  // Open the file for writing
  File file = SPIFFS.open(filename, "w");

  // Check if the file was opened successfully
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }

  // Write data to the file
  if (file.print(data)) {
    Serial.println("File saved successfully.");

    // Close the file after writing
    file.close();

    // Now, open the file for reading
    file = SPIFFS.open(filename, "r");

    // Check if the file was opened successfully for reading
    if (file) {
      // Serial.println("Reading file:");

      // Read and print the contents of the file
      // while (file.available()) {
      //   Serial.write(file.read());
      // }
      // Serial.println(); // Print a newline after reading

      // Close the file after reading
      file.close();
    } else {
      Serial.println("Error opening file for reading");
    }
  } else {
    Serial.println("Error saving file.");
  }
}


// The HTML content of your survey form
const char* htmlContent = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>Survey Form</title>
  <link href="style.css" rel="stylesheet" type="text/css" />
</head>
<body>
  <!-- Survey Form -->
  <form id="surveyForm">
    <!-- Age Range Question -->
    <p>Age Range:</p>
    <input type="radio" id="age1" name="age" value="18-24">
    <label for="age1">18-24</label><br>
    <input type="radio" id="age2" name="age" value="25-34">
    <label for="age2">25-34</label><br>
      <input type="radio" id="age3" name="age" value="35-44">
      <label for="age3">35-44</label><br>
      <input type="radio" id="age4" name="age" value="45-55">
      <label for="age4">45-55</label><br>
      <input type="radio" id="age5" name="age" value="55+">
      <label for="age5">55+</label><br>

      <!-- Gender Question -->
      <p>Gender:</p>
      <input type="radio" id="gender1" name="gender" value="Male">
      <label for="gender1">Male</label><br>
      <input type="radio" id="gender2" name="gender" value="Female">
      <label for="gender2">Female</label><br>
      <input type="radio" id="gender3" name="gender" value="Non-binary">
      <label for="gender3">Non-binary</label><br>
      <input type="radio" id="gender4" name="gender" value="Prefer not to say">
      <label for="gender4">Prefer not to say</label><br>
    
    <!-- Interests/Hobbies Question -->
    <p>Interests/Hobbies (choose 5):</p>
    <input type="checkbox" id="hobby1" name="hobby" value="Sports">
    <label for="hobby1">Sports</label><br>
    <input type="checkbox" id="hobby2" name="hobby" value="Fashion">
    <label for="hobby2">Fashion</label><br>
    <input type="checkbox" id="hobby3" name="hobby" value="Gaming">
    <label for="hobby3">Gaming</label><br>
    <input type="checkbox" id="hobby4" name="hobby" value="Food">
    <label for="hobby4">Food</label><br>
    <input type="checkbox" id="hobby5" name="hobby" value="Cooking">
    <label for="hobby5">Cooking</label><br>
    <input type="checkbox" id="hobby6" name="hobby" value="Animals">
    <label for="hobby6">Animals</label><br>
    <input type="checkbox" id="hobby7" name="hobby" value="Comedy">
    <label for="hobby7">Comedy</label><br>
    <input type="checkbox" id="hobby8" name="hobby" value="Fitness">
    <label for="hobby8">Fitness</label><br>
    <input type="checkbox" id="hobby9" name="hobby" value="Books">
    <label for="hobby9">Books</label><br>
    <input type="checkbox" id="hobby10" name="hobby" value="Film">
    <label for="hobby10">Film</label><br>
    <input type="checkbox" id="hobby11" name="hobby" value="Music">
    <label for="hobby11">Music</label><br>
    <input type="checkbox" id="hobby12" name="hobby" value="Sustainability">
    <label for="hobby12">Sustainability</label><br>
    <input type="checkbox" id="hobby13" name="hobby" value="LGBTQ+">
      <label for="hobby13">LGBTQ+</label><br>
      <input type="checkbox" id="hobby14" name="hobby" value="Photography">
      <label for="hobby14">Photography</label><br>
      <input type="checkbox" id="hobby15" name="hobby" value="Technology">
      <label for="hobby15">Technology</label><br>
      <input type="checkbox" id="hobby16" name="hobby" value="News">
      <label for="hobby16">News</label><br>
      <input type="checkbox" id="hobby17" name="hobby" value="Politics">
      <label for="hobby17">Politics</label><br>
      <input type="checkbox" id="hobby18" name="hobby" value="Travel">
      <label for="hobby18">Travel</label><br>
      <input type="checkbox" id="hobby19" name="hobby" value="Outdoors">
      <label for="hobby19">Outdoors</label><br>
    <input type="submit" value="Submit">
  </form>

  

  <!-- Placeholder for displaying responses -->
  <div id="responseDisplay"></div>

  <script>
    document.getElementById('surveyForm').addEventListener('submit', function(event) {
      event.preventDefault(); // Prevent the default form submission

      var response = '';

      // Handling Age Range
      var ageElements = document.getElementsByName('age');
      for (var i = 0; i < ageElements.length; i++) {
        if (ageElements[i].checked) {
          response += ageElements[i].value + ',';
          break;
        }
      }

      // Handling Gender
      var genderElements = document.getElementsByName('gender');
      for (var i = 0; i < genderElements.length; i++) {
        if (genderElements[i].checked) {
          response += genderElements[i].value + ',';
          break;
        }
      }
      // Handling Interests/Hobbies
          var hobbiesResponse = [];
          var hobbyElements = document.getElementsByName('hobby');
          for (var i = 0; i < hobbyElements.length; i++) {
            if (hobbyElements[i].checked) {
              hobbiesResponse.push(hobbyElements[i].value);
            }
          }
          if (hobbiesResponse.length > 0) {
            response += hobbiesResponse.join(',');
          }
        response += ',';

          // Display the response string in the 'responseDisplay' div
      document.getElementById('responseDisplay').innerText = response;

      // Create a FormData object to send data to the server
      var formData = new FormData();
      formData.append('response', response);

      // Send the data to the server using fetch
      fetch('/saveData', {
        method: 'POST',
        body: formData
      })
      .then(response => response.text())
      .then(data => {
        console.log(data); // Log the response from the server
        // Optionally, update the UI to show that the data has been submitted
      });

    });
  </script>
</body>
</html>

)rawliteral";

void setup() {
  //SPIFFS.format();  // Uncomment this line to format SPIFFS
  Serial.begin(115200);
   // Mount SPIFFS without formatting
  if (!SPIFFS.begin(false)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  // Set up ESP32 as an access point
  WiFi.softAP(ssid, password);

  // Wait for the access point to be fully set up
  while (WiFi.softAPIP() == IPAddress(0, 0, 0, 0)) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Get IP address of the access point
  IPAddress ipAddress = WiFi.softAPIP();
  Serial.print("Access Point IP Address: ");
  Serial.println(ipAddress);

  // Define the survey form web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlContent);
  });

  // Handle form submission and save data to a file
  server.on("/saveData", HTTP_POST, [](AsyncWebServerRequest *request){
    // Check if the request has a file attached
    if (request->hasParam("response", true)) {
      AsyncWebParameter* p = request->getParam("response", true);

      // Save the response data to a file
      saveStringToFile(p->value(), "/user2Data.txt");

      // Compare with preferences and person files
      compareData();

      // Send a response to the client
      request->send(200, "text/plain", "Data saved successfully!");
    } else {
      request->send(400, "text/plain", "Bad Request");
    }
  });

  // Start server
  server.begin();
}

void loop() {
  // Your code here
}

void compareData() {
  // Current user's preferences
  File prefsFile = SPIFFS.open("/userData.txt", "r");
  if (!prefsFile) {
      Serial.println("Unable to open file: userData.txt");
      return;
  }
  
  // Person's profile for comparison
  File personFile = SPIFFS.open("/user2Data.txt", "r");
  if (!personFile) {
      Serial.println("Unable to open file: user2Data.txt");
      prefsFile.close();
      return;
  }
  
  // Keep score of similarities/matches between files
  int score = 0;
  char buffer[1024];

  // Check age
  String prefAge = prefsFile.readStringUntil(',');
  String realAge = personFile.readStringUntil(','); 
  if (prefAge.equals(realAge)) {
    score++;
    Serial.println("Age matches, incrementing score");
  }

  // Check gender
  String prefGender = prefsFile.readStringUntil(',');
  String realGender = personFile.readStringUntil(',');
  if (prefGender.equals(realGender)) {
    score++;
    Serial.println("Gender matches, incrementing score");
  }

  // Increment score for each matching hobby
  String prefHobbies[5];
  for (int i = 0; i < 5; i++) {
      prefHobbies[i] = prefsFile.readStringUntil(','); 
  }

  String personHobbies[5];
  for (int i = 0; i < 5; i++) {
      personHobbies[i] = personFile.readStringUntil(',');
  }

  for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
          if (prefHobbies[i].equals(personHobbies[j])) {
            score++;
            Serial.println("Hobby matches, incrementing score");
          }
      }
  }

  // If at least one hobby matches, vibrate
  if (score >= 3) {
    Serial.println("~~~vibration~~~~ found a friend");
    Serial.println(score);
  } else {
    Serial.println("incompatible :((");
    Serial.println(score);
  }

  prefsFile.close();
  personFile.close();
}
