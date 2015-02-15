import os
import json

def static(result, correct, miss, *args):
    # initialize the total number of miss and correct predictions
    missPrediction = 0
    correctPrediction = 0

    # iterate over the result get calculate the miss prediction rate
    for instructionAddress, value in result.iteritems():

        # if profile guided, then branch addresses taken 50% or more of the time, so correct prediction is whichever greater than the other
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
    historyRegisterTable = {}
    patternHistoryTable = {}

    initGlobalHistoryRegister = [0] * k
    strInitGHR = str(initGlobalHistoryRegister).strip('[]').replace(',', '').replace(' ', '')

    initPredictor = 1

    missPrediction = 0
    totalOutcome = 0

    for instructionAddress, value in result.iteritems():

        historyRegisterTable.update({instructionAddress:strInitGHR})
        patternHistoryTable.update({strInitGHR:initPredictor})
        globalHistoryRegister = strInitGHR
        
        for actualOutcome in value["orderedOutcome"]:

            predictor2bits = patternHistoryTable[globalHistoryRegister]

            predictionTaken = (predictor2bits >= 2)

            branchTaken = (actualOutcome == 1)

            if (predictionTaken != branchTaken):
                missPrediction+=1

            if (branchTaken and (predictor2bits < 3)):
                predictor2bits+=1
            if (not branchTaken and (predictor2bits > 0)):
                predictor2bits-=1

            patternHistoryTable[globalHistoryRegister] = predictor2bits

            globalHistoryRegister = list(globalHistoryRegister)[1:k]
            if (actualOutcome == 1):
                globalHistoryRegister.append('1')
            else:
                globalHistoryRegister.append('0')
            globalHistoryRegister = str(globalHistoryRegister).strip('[]').replace(', ', '').replace('\'', '')

            if globalHistoryRegister not in patternHistoryTable:
                patternHistoryTable.update({globalHistoryRegister:initPredictor})

        patternHistoryTable = {}
        totalOutcome += len(value["orderedOutcome"])

    # calculate miss prediction rate and print to the console
    mpr = missPrediction / float(totalOutcome) * 100
    print ("Miss Prediction Rate: {0:.4f}%".format(mpr))


def read_file(filename):
    result = {}
    inputFile = open(filename, "r")
    for line in inputFile:

        instructionAddress = line[2:8]
        outcome = line[9]

        if instructionAddress not in result:
            outcomesDictionary = {}

            if (outcome == '0'):
                outcomesDictionary.update({0:1,1:0,"orderedOutcome":[0]})
            else:
                outcomesDictionary.update({0:0,1:1,"orderedOutcome":[1]})

            result.update({instructionAddress:outcomesDictionary})

        else:
            if (outcome == '0'):
                result[instructionAddress][0]+=1
                result[instructionAddress]["orderedOutcome"].append(0)
            else:
                result[instructionAddress][1]+=1
                result[instructionAddress]["orderedOutcome"].append(1)

    inputFile.close()

    return result


def output_sample_result(result):
    with open('Sample_Result.json', 'w') as sampleResult:
        json.dump(result, sampleResult, sort_keys=True, indent=4, separators=(',', ': '))
    sampleResult.close()


def main():
    # read trace files
    # filename = 'test.out'
    filename = 'gcc_branch.out'
    # filename = 'mcf_branch.out'
    # filename = raw_input('Enter input filename: ')
    # while not os.path.exists(filename):
    #     filename = raw_input('File doesn\'t exists, enter again:')

    result = read_file(filename)
    # output_sample_result(result)

    print("Static branch: always taken")
    static(result, 1, 0)

    print("\nStatic branch: always not taken")
    static(result, 0, 1)

    print("\nStatic branch: profile guided")
    static(result, 0, 1, "profile guided")

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