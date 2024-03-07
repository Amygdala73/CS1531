import math

class Circle():
    def __init__(self, radius):
        self.radius = radius

    def circumference(self):
        return 2 * self.radius * math.pi

    def area(self):
        return self.radius * self.radius * math.pi



