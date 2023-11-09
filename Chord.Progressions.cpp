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

    MakeProgression(key, attribute, length);

    return 0;
}
