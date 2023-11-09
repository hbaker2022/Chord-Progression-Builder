/*Dev notes:
This is functional, and works to literally just generate random major/minor chord progressions,
but it needs to generate more accurately happy major/ minor chord progressions.
I think the general way you could implement this is by assigning more emphasis on the major chords in
the key by making it more likely to generate a 0, 4, and 5 for major keys, and a i, ii, 4, and 5 for minor keys.

Likewise, it should generate less amounts of specific chords, and maybe get some patterns, where it generates
chords for 1/2 of progLength, and then repeats that with a slight modification again to make a progression with repetition


After you do that you will be in a good place to add more features, like adding different chord types etc. but this is
a good starting point
*/

/* MAJOR: If you want to add chords to give it a certain
feeling (like an augmented chord for "spooky" sound), you could use a vector and push/pop_back, and add in
 a chord of that type to the vector storing the different chord numbers.

The array for a minor key has 7 elements, one for each minor/major/diminished chord in the key.
So if we wanted to make a chord progression with a blues-y sound, you could do
majorVector.pop_back(2), making the vector 5 chords long. Then you could reassign the different elements
with their respective tones in the pentatonic scale.

*/
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

/*This function stores all of the different chords in a scale, given an attribute for how the progression
should sound. If it should sound bluesy, chordVec will only store the chords of the pentatonic scale,
 if it should sound spooky, chordVec will store the chords in the harmonic minor scale, plus an augmented
 chord. This function basically acts as your database
 */


vector<pair<string, int> > MajorOrMinor(string key, string attribute){

    vector<pair<string, int> > chordVec;

    vector<pair<string, int> > majorVec;

    majorVec = {{"I", 5}, {"ii", 3}, {"iii", 4}, {"IV", 5}, {"V", 4}, {"vi", 4}, {"viiº", 1 }};

    vector<pair<string, int> > minorVec = {{"i", 5}, {"iiº", 3}, {"III", 3}, {"iv", 5}, {"v", 5}, {"VI", 3}, {"VII", 2}};

    if(key == "major" || key == "Major"){
        chordVec = majorVec;
    }
    if(key == "minor" || key == "Minor"){
        chordVec = minorVec;
    }


    return chordVec;
}

/*MakeProgression puts together the chord progression by assigning chordVec with the chords given an
 attribute via calling DataBase with attribute as the arguement. Through random number generation it
 puts together a random combination of chords for length progLength.

 Ways to improve: Weight the most important chords using chatGPT's help. The I, IV, and V chord should
 be waited higher than the minor chords in a happy progression, and the viº chord should be essentially
 impossible to get when compared with the major and minor chords.

 */
void MakeProgression(string key, string attribute, int progLength) {

    vector<pair<string, int> > chordVec = MajorOrMinor(key, attribute);

    int totalWeight = 0;
    for (auto &chord : chordVec) {
        totalWeight += chord.second;
    }


    cout << "Your progression is: ";

    for(int i = 0; i < progLength; ++i) {
        int rnd = rand() % totalWeight;
        for (auto &chord: chordVec) {
            if (rnd < chord.second) {
                cout << chord.first << " ";
                break;
            }
            rnd -= chord.second;
        }
    }

}

int main() {
    //Sets the seed for the random number to time

    srand(static_cast<unsigned int>(time(nullptr)));

    //necessary variables
    string attribute;
    string key;
    int length;

    cout << "What key? ";
    cin >> key;
    cout << "How do you want it to sound? ";
    cin >> attribute;
    cout << "How many chords ";
    cin >> length;

    //Call to the function that prints out the progression

    MakeProgression(key, attribute, length);

    return 0;
}
