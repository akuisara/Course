import os
import json

def static(result, correct, miss, *args):
    """ 
    iterate over the result dictionary, count the total number of miss predictions and correct predictions in order to calculate the miss prediction rate
    Args: result - a dictionary, keys: instruction addresses, values: outcomes
          correct - if prediction is always taken, then correct = 1; if prediction is always not taken, then correct = 0; if prediction is profile guided, then correct can be either 1 or 0, but must be different from miss
          miss - if prediction is always taken, then miss = 0; if prediction is always not taken, then miss = 1; if prediction is profile guided, then miss can be either 1 or 0, but must be different from correct
          *args - if "profile guided" in *args, then the prediction is profile guided, branch taken 50 percent or more of the time recorded as branch taken
    Returns: none
    """
    # initialize the total number of miss and correct predictions
    missPrediction = 0
    correctPrediction = 0

    # iterate over the result dictionary to count the total number of correct and miss predictions
    for instructionAddress, value in result.iteritems():

        # if profile guided, then branch addresses taken 50% or more of the time indicates branch taken, so correct prediction is whichever greater than the other
        if "profile guided" in args:
            if (value[miss] > value[correct]):
                temp = miss
                miss = correct
                correct = temp

        # increment number of miss predictions and correct predictions
        missPrediction += value[miss]
        correctPrediction += value[correct]

    # calculate miss prediction rate and print to the console
    mpr = missPrediction / float(missPrediction + correctPrediction) * 100
    print ("Miss Prediction Rate: {0:.4f}%".format(mpr))


def dynamic(result, k):
    """ 
    iterate over the result dictionary, count the total number of miss predictions and total number of outcomes in order to calculate the miss prediction rate
    Args: result - a dictionary, keys: instruction addresses, values: outcomes
          k - length of global history registers, which have initial value of all 0s
    Returns: none
    """
    historyRegisterTable = {} # initialize the History Register Table
    patternHistoryTable = {}  # initialize the Pattern History table
    missPrediction = 0        # initialize total number of miss predictions
    totalOutcome = 0          # initialize total number of outcomes

    # initialize the predictor to 1 - weakly not taken (01) 
    # (0 or 00 - not taken; 1 or 01 - weakly not taken; 2 or 10 - weakly taken; 3 or 11 - taken)
    initPredictor = 1         

    #initialize global history register to all 0s and convert the list to a string
    initGlobalHistoryRegister = [0] * k 
    strInitGHR = str(initGlobalHistoryRegister).strip('[]').replace(',', '').replace(' ', '')

    # iterate over the result dictionary to count the total number of outcomes and miss predictions
    for instructionAddress, value in result.iteritems():

        # initialize GHR table and PHT table
        historyRegisterTable.update({instructionAddress:strInitGHR})
        patternHistoryTable.update({strInitGHR:initPredictor})
        globalHistoryRegister = strInitGHR
        
        # iterate over the value["orderedOutcome"] list to get the actual outcomes
        for actualOutcome in value["orderedOutcome"]:
            # get the prediction from the PHT
            predictor2bits = patternHistoryTable[globalHistoryRegister]
            predictionTaken = (predictor2bits >= 2)

            # check if branch is actually taken or not
            branchTaken = (actualOutcome == 1) 

            # if miss predicted, increment missPrediction
            if (predictionTaken != branchTaken):
                missPrediction+=1

            # update the 2-bit predictor based on the actual outcome
            if (branchTaken and (predictor2bits < 3)):
                predictor2bits+=1
            if (not branchTaken and (predictor2bits > 0)):
                predictor2bits-=1
            patternHistoryTable[globalHistoryRegister] = predictor2bits

            # update the global history register based on the actual outcome
            globalHistoryRegister = list(globalHistoryRegister)[1:k]
            if (actualOutcome == 1):
                globalHistoryRegister.append('1')
            else:
                globalHistoryRegister.append('0')
            globalHistoryRegister = str(globalHistoryRegister).strip('[]').replace(', ', '').replace('\'', '')

            # add the updated global history register to be a new key in PHT if it doesn't exist
            if globalHistoryRegister not in patternHistoryTable:
                patternHistoryTable.update({globalHistoryRegister:initPredictor})

        # after finished one instruction address, flush the old PHT and increment the total outcomes
        patternHistoryTable = {}
        totalOutcome += len(value["orderedOutcome"])

    # calculate miss prediction rate and print to the console
    mpr = missPrediction / float(totalOutcome) * 100
    print ("Miss Prediction Rate: {0:.4f}%".format(mpr))


def read_file(filename):
    """ 
    read the file and generate a dictionary contains stats and information of input file
    Arg: filename - filename entered by user
    Returns: result - the dictionary, keys: instruction addresses, values: outcomes
    """
    result = {} # initialize a result dictionary, where keys are instruction addresses
    inputFile = open(filename, "r")
    for line in inputFile:
        # get instruction addresses and actual outcomes from each line
        instructionAddress = line[2:8] 
        outcome = line[9]

        # if instruction address is not in the result dictionary, then add it with initial values 
        if instructionAddress not in result:

            # initialize an outcome dictionary with initial value based on the first outcome
            outcomesDictionary = {} 
            if (outcome == '0'):
                outcomesDictionary.update({0:1,1:0,"orderedOutcome":[0]})
            else:
                outcomesDictionary.update({0:0,1:1,"orderedOutcome":[1]})
            result.update({instructionAddress:outcomesDictionary})

        else:
            # increment the total number of outcomes, and append the outcome to orderedOutcome list
            if (outcome == '0'):
                result[instructionAddress][0]+=1
                result[instructionAddress]["orderedOutcome"].append(0)
            else:
                result[instructionAddress][1]+=1
                result[instructionAddress]["orderedOutcome"].append(1)

    inputFile.close()

    return result


def output_sample_result(result):
    """ 
    dump the result dictionary to Sample_Result.json
    Arg: result - a dictionary, keys: instruction addresses, values: outcomes
    Returns: none 
    """

    with open('Sample_Result.json', 'w') as sampleResult:
        json.dump(result, sampleResult, sort_keys=True, indent=4, separators=(',', ': '))
    sampleResult.close()


def count_outcomes(result):
    """ 
    get the most frequent instruction address with total number of occurrences, and calculate the average occurrence for all instruction addresses
    Arg: result - a dictionary, keys: instruction addresses, values: outcomes
    Returns: none 
    """
    mostFrequentInstruction = 0
    mostFrequentInstructionCount = 0
    totalOccurrences = 0

    # iterate over the result dictionary to count the total number of outcomes and found the most frequent instruction address    
    for instructionAddress, value in result.iteritems():
        totalOccurrences += len(value["orderedOutcome"])
        if (len(value["orderedOutcome"]) > mostFrequentInstructionCount):
            mostFrequentInstruction = instructionAddress
            mostFrequentInstructionCount = len(value["orderedOutcome"])

    print "\nMost frequent instruction: " + mostFrequentInstruction + " occurs " + str(mostFrequentInstructionCount) + " times"

    averageOccurrences = float(totalOccurrences) / len(result)
    print ("Average instruction occurrences: {0:.2f} times".format(averageOccurrences))


def main():
    # read the trace file
    filename = raw_input('Enter input filename: ')
    # prompt user to reenter filename if file doesn't exist
    while not os.path.exists(filename):
        filename = raw_input('File doesn\'t exist, enter again:')

    # get the result dictionary, where the keys are instruction addresses, values are outcomes
    result = read_file(filename)

    # write the result to an output JSON file
    # output_sample_result(result)

    # count outcomes - used to analyze result
    # count_outcomes(result)

    # print out the results to the console
    print("\nStatic branch: always taken")
    static(result, 1, 0)

    print("\nStatic branch: always not taken")
    static(result, 0, 1)

    print("\nStatic branch: profile guided")
    static(result, 0, 1, "profile guided")
    # same as above
    # static(result, 1, 0, "profile guided")

    print("\nDynamic branch: Two-Level Correlating Predictor with K = 4")
    dynamic(result, 4)

    print("\nDynamic branch: Two-Level Correlating Predictor with K = 8")
    dynamic(result, 8)
    
    print("\nDynamic branch: Two-Level Correlating Predictor with K = 12")
    dynamic(result, 12)

    print("\nDynamic branch: Two-Level Correlating Predictor with K = 16")
    dynamic(result, 16)


if __name__ == '__main__':
    main()