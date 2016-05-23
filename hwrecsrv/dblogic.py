import MySQLdb

class DatabaseLogic:
    def __init__(self):
        self.db = MySQLdb.connect("localhost", "lpqs", "abc123", "lpqs")
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

if __name__ == "__main__":
    dbl = DatabaseLogic()
    petnum = dbl.getPetitionerNumbers()

    for row in petnum:
        print(row)

