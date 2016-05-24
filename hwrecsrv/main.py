from dblogic import DatabaseLogic
import sys

def main():
    dbl = DatabaseLogic()

    print('--- LPQS Temporary Menu ---')
    categories = dbl.getCategories()

    for cat in categories:
        print(cat)

    x = input('Category ID: ')
    num = dbl.getLastPetitionerNumberForCategory(x)
    if num != None:
        print("Last number " + num[0])
    else:
        print("No number for this category, yet.")

    return 0

if __name__ == "__main__":
    sys.exit(main())
