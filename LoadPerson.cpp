struct RangeAge {
    int min;
    int max;
};
struct DbInfo {
    string_view name;
    int connection_timeout;
    bool allow_exceptions;
    DbLogLevel log_level;
};

vector<Person> LoadPerson(const DbInfo& db_info, const RangeAge& range_age, string_view name_filter) {
    DBConnector connector(db_info.allow_exceptions, db_info.log_level);
    DBHandler db;
    if (db_info.name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_info.name, db_info.connection_timeout);
    }
    else {
        db = connector.Connect(db_info.name, db_info.connection_timeout);
    }
    if (!db_info.allow_exceptions && !db.IsOK()) {
        return {};
    }
    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << range_age.min << " and "s << range_age.max << " "s
        << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());
    
    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}
