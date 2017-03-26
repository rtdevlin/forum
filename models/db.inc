<?php
include_once ('include/Logger.inc');

class Db {
    public static function getDb() {
        try {
            $fileName = "Forum.db3";

            // see if we need to create tables
            $makeDb = !file_exists($fileName);
            $db = new PDO("sqlite:${fileName}");

            // force exceptions for better debugging.
            $db -> setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            // force cascading deletes on foreign key constraints
            $st = $db -> prepare("PRAGMA foreign_keys = ON");
            $st -> execute();

            if ($makeDb) {
                self::makeTables($db);
                self::populateTables($db);
            }

        } catch (PDOException $e) {
            die("Could not open database. " . $e -> getMessage());
        }
        return $db;
    }

    private static function makeTables(&$db) {

        Logger::instance() -> info("Creating tables");
        // @formatter:off
        $statements = array(
          "CREATE TABLE `users` (
            `user_id` INTEGER PRIMARY KEY AUTOINCREMENT,
            `first_name`  TEXT NOT NULL,
            `last_name` TEXT NOT NULL,
            `email` TEXT UNIQUE,
            `password`  TEXT NOT NULL
          );",
          "CREATE TABLE `questions` (
            `id`  INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            `title` TEXT NOT NULL,
            `content` TEXT NOT NULL,
            `tags`  TEXT,
            `date`  NUMERIC,
            `user_id` INTEGER NOT NULL,
            FOREIGN KEY(`user_id`) REFERENCES users(id)
            );",
          "CREATE TABLE `answers` (
            `answer_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            `content` TEXT NOT NULL,
            `insert_ts` NUMERIC DEFAULT CURRENT_TIMESTAMP,
            `question_id` INTEGER NOT NULL,
            `user_id` INTEGER NOT NULL,
            FOREIGN KEY(`question_id`) REFERENCES questions ( id ),
            FOREIGN KEY(`user_id`) REFERENCES users(id)
          );"
        );
        // @formatter:on

        $db -> beginTransaction();
        foreach ($statements as $statement) {
            $st = $db -> prepare($statement);
            $st -> execute();
        }
        $db -> commit();
    }
}
?>
