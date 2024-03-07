from coverage import Coverage
import sys

exercises = {
    "acronym": 2.5,
    "filter": 2.5,
    "frequency": 2.5,
    "mono": 2.5,
    "penguin": 2.5,
    "trouble": 5
}

if __name__ == "__main__":
    cov = Coverage('.coverage')
    cov.load()
    for exercise, value in exercises.items():
        _, _, excluded, missing, _ = cov.analysis2(f"{exercise}.py")
        if exercise in sys.argv and not missing:
            if not excluded:
                print(f"{exercise}_cov|{value}|", end='')
            else:
                print(f"{exercise}_cov|{value - 1}|", end='')

