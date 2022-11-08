#include "accounts.h"

void UserAcc::display_tickets() {}
void UserAcc::sort_tickets() {}
void UserAcc::filter_tickets() {}
void UserAcc::find_ticket() {}

bool UserAcc::sign_in() { return true; }
bool UserAcc::sign_up() { return true; }

void UserAcc::fill_balance() {}
void UserAcc::see_balance() {}
void UserAcc::buy_ticket() {}
void UserAcc::check_history() {}

void UserAcc::readInfo() {}
void UserAcc::writeInfo() {}

//////////////////////////////////////

void AdminAcc::display_tickets() {}
void AdminAcc::sort_tickets() {}
void AdminAcc::filter_tickets() {}
void AdminAcc::find_ticket() {}

void AdminAcc::display_stations() {}
void AdminAcc::sort_stations() {}
void AdminAcc::filter_stations() {}
void AdminAcc::find_station() {}

bool AdminAcc::sign_in() { return true; }
bool AdminAcc::sign_up() { return true; }

void AdminAcc::create_ticket() {}
void AdminAcc::delete_ticket() {}
void AdminAcc::edit_ticket() {}

void AdminAcc::add_station() {}
void AdminAcc::remove_station() {}
void AdminAcc::edit_station() {}

void AdminAcc::readInfo() {}
void AdminAcc::writeInfo() {}