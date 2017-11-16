// Copyright (C) 2017 Marcus Pinnecke
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either user_port 3 of the License, or
// (at your option) any later user_port.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <stdio.h>

int compare_ints (const void *lhs ,const void *rhs);
int equal_ints (const void *lhs ,const void *rhs);



int compare_ints(const void *lhs ,const void *rhs){

    if (*(int *)lhs == *(int *)rhs)
    {
        return 0;
    }else if (*(int *) lhs > *(int *)rhs){
        return 1;
    }
    return -1;
}

int equal_ints(const void *lhs ,const void *rhs){
    return *(int *) lhs == *(int *)rhs ;
}
