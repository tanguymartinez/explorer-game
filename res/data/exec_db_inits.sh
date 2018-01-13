#!/bin/bash

./init_db.sh explorer.sqlite3 init_tables.sql
./feed_db.sh explorer.sqlite3 raw/map_raw raw/entities_raw raw/animations_raw raw/replies_raw
