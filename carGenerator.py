import random

def main():
    fparameters = open("carParameters", "w")
    cars = 10
    for i in range(cars):
        if i < cars/2:
            x = random.randrange(-50, 51, 10)
            y = 0
            direction = 0
        else:
            x = 0
            y = random.randrange(-50, 51, 10)
            direction = 1

        app = random.randrange(0, 3, 1)
        url = random.randrange(0, 3, 1)
        sentido = random.choice([-1, 1])
        vel = random.randrange(10, 21, 5)
        size = random.randrange(3, 6, 1)
        reckless = random.randrange(0, 2, 1)

        car = "{:3}{:3}{:3}{:3}{:3}{:3}{:3}{:3}{:3}\n".format(
            x, y, vel, direction, sentido, size, app, url, reckless)
        fparameters.write(car)
    fparameters.close()

if __name__ == "__main__":
    main()
