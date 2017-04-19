// Given an array of strings, produce a single string as follows:
// Repeat the following steps while there is more than one string in the array:
// * find the shortest string in the array (if there are several strings of the same length take the leftmost one);
// * find the shortest string among the rest (if there are several strings of the same length take the rightmost one);
// * extract the chosen strings from the array;
// * append the result of their concatenation (the second string should be added to the end of the first string) to the right end of the array.
// After the algorithm has finished, there will be a single string left in the array. Return that string.
// Example
// For init = ["aaa", "dd", "bbbbb"], the output should be
// concatenationProcess(init) = "bbbbbddaaa".

std::string concatenationProcess(std::vector<std::string> init) {

  while (init.size() > 1) {
    int minInd1 = 0,
        minInd2 = init.size()-1 ;

    for (int i = 1; i < init.size(); i++) {
      if (init[i].size() < init[minInd1].size()) {
        minInd1 = i;
      }
    }

    if (minInd2 == minInd1) {
      minInd2--;
    }

    for (int i = init.size() - 2; i >= 0; i--) {
      if (init[i].size() < init[minInd2].size()
       && i != minInd1) {
        minInd2 = i;
      }
    }

    init.push_back(init[minInd1] + init[minInd2]);
    init.erase(init.begin() + std::max(minInd1, minInd2));
    init.erase(init.begin() + std::min(minInd1, minInd2));
  }

  return init[0];
}
