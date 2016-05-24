import MySQLdb

class DatabaseLogic:
    def __init__(self):
        self.db = MySQLdb.connect("localhost", "hostel", "abc123", "lpqs")
        self.cursor = self.db.cursor()

    def __del__(self):
        self.db.close()
    
    def getPetitionerNumbers(self):
        sql = """SELECT p.generatedNum, o.name, s.name FROM petitioner_number p
            LEFT JOIN position o ON p.position_id = o.id
            JOIN status s ON p.status_id = s.id
            WHERE s.name <> 'End'"""
        
        self.cursor.execute(sql)
        return self.cursor.fetchall()

    def getCategories(self):
        sql = """SELECT * FROM case_category
            WHERE active = 1"""

        self.cursor.execute(sql)
        return self.cursor.fetchall()

    def getLastPetitionerNumberForCategory(self, categoryId):
        sql = """SELECT generatedNum FROM petitioner_number
            WHERE case_category_id = {0}
            ORDER BY createdOn DESC, generatedNum DESC
            LIMIT 1"""

        self.cursor.execute(sql.format(categoryId))
        return self.cursor.fetchone()

    def insertNewNumber(self, categoryId, generatedNum):
        sql = """INSERT INTO petitioner_number (status_id, case_category_id, generatedNum, createdOn) VALUES
            (1, {0}, "{1}", NOW())"""

        try:
            self.cursor.execute(sql.format(categoryId, generatedNum))
            self.db.commit()
        except:
            self.db.rollback()

    def getCategoryId(self, categoryName):
        sql = """SELECT id FROM case_category
            WHERE name = "{0}" """

        self.cursor.execute(sql.format(categoryName))
        return self.cursor.fetchone()

