from time import sleep
import matplotlib.pyplot as plt

yArray = []

def main():
    global yArray, ky, kx

    while True:
        Data = open("C:\Programming\Alg&Data\Lab1\Lab1\Lab1\GraphData.txt", "r")

        yArray = Data.read().split()
        yArray = [int(number) for number in yArray]

        xArray = [i for i in range (len(yArray))]

        plt.plot(xArray, yArray)
        plt.show()
        Data.close()
        sleep(1)
        plt.close()


if __name__ == "__main__":
    main()

