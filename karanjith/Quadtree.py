class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return f"({self.x}, {self.y})"

class Boundary:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def contains(self, point):
        return (self.x - self.width <= point.x < self.x + self.width and
                self.y - self.height <= point.y < self.y + self.height)

    def intersects(self, range):
        return not (range.x - range.width > self.x + self.width or
                    range.x + range.width < self.x - self.width or
                    range.y - range.height > self.y + self.height or
                    range.y + range.height < self.y - self.height)

class Quadtree:
    def __init__(self, boundary, capacity):
        self.boundary = boundary
        self.capacity = capacity
        self.points = []
        self.divided = False

    def subdivide(self):
        x = self.boundary.x
        y = self.boundary.y
        w = self.boundary.width
        h = self.boundary.height

        ne = Boundary(x + w / 2, y - h / 2, w / 2, h / 2)
        nw = Boundary(x - w / 2, y - h / 2, w / 2, h / 2)
        se = Boundary(x + w / 2, y + h / 2, w / 2, h / 2)
        sw = Boundary(x - w / 2, y + h / 2, w / 2, h / 2)

        self.northeast = Quadtree(ne, self.capacity)
        self.northwest = Quadtree(nw, self.capacity)
        self.southeast = Quadtree(se, self.capacity)
        self.southwest = Quadtree(sw, self.capacity)
        self.divided = True

    def insert(self, point):
        if not self.boundary.contains(point):
            return False

        if len(self.points) < self.capacity:
            self.points.append(point)
            return True
        else:
            if not self.divided:
                self.subdivide()

            if self.northeast.insert(point): return True
            if self.northwest.insert(point): return True
            if self.southeast.insert(point): return True
            if self.southwest.insert(point): return True

        return False

    def query(self, range, found_points=None):
        if found_points is None:
            found_points = []

        if not self.boundary.intersects(range):
            return found_points

        for point in self.points:
            if range.contains(point):
                found_points.append(point)

        if self.divided:
            self.northwest.query(range, found_points)
            self.northeast.query(range, found_points)
            self.southwest.query(range, found_points)
            self.southeast.query(range, found_points)

        return found_points

if __name__ == "__main__":
    boundary = Boundary(200, 200, 200, 200)
    qt = Quadtree(boundary, 4)
    qt.insert(Point(50, 50))
    qt.insert(Point(150, 150))
    qt.insert(Point(250, 250))
    qt.insert(Point(350, 350))
    print(qt.query(Boundary(200, 200, 200, 200)))
