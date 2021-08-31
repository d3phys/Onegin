#ifndef ONEGIN_H_
#define ONEGIN_H_

enum exit_code {
    SUCCEED    = 0,
    ERR_FOPEN  = 1,
    ERR_FCLOSE = 2,
};

exit_code onegin_client();

#endif // ONEGIN_H_
