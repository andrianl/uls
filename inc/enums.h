#pragma once


typedef enum format format;

enum acl_type
{
    ACL_T_NONE,
    ACL_T_LSM_CONTEXT_ONLY,
    ACL_T_YES
};

enum filetype
{
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
    sock,
    whiteout,
    arg_directory
};

enum Dereference_symlink
{
    DEREF_UNDEFINED = 1,
    DEREF_NEVER,
    DEREF_COMMAND_LINE_ARGUMENTS,      /* -H */
    DEREF_COMMAND_LINE_SYMLINK_TO_DIR, /* the default, in certain cases */
    DEREF_ALWAYS                       /* -L */
};

enum format
{
    long_format,   /* -l and other options that imply -l */
    one_per_line,  /* -1 */
    many_per_line, /* -C */
    horizontal,    /* -x */
    with_commas    /* -m */
};

/* 'full-iso' uses full ISO-style dates and times.  'long-iso' uses longer
   ISO-style timestamps, though shorter than 'full-iso'.  'iso' uses shorter
   ISO-style timestamps.  'locale' uses locale-dependent timestamps.  */
enum time_style
{
    full_iso_time_style, /* --time-style=full-iso */
    long_iso_time_style, /* --time-style=long-iso */
    iso_time_style,      /* --time-style=iso */
    locale_time_style    /* --time-style=locale */
};

// enum time_type
// {
//     time_atime,
//     time_atime,
//     time_atime,
//     time_ctime,
//     time_ctime
// };

enum ignore_mode
{
    /* Ignore files whose names start with '.', and files specified by
       --hide and --ignore.  */
    IGNORE_DEFAULT,

    /* Ignore '.', '..', and files specified by --ignore.  */
    IGNORE_DOT_AND_DOTDOT,

    /* Ignore only files specified by --ignore.  */
    IGNORE_MINIMAL
};

enum indicator_style
{
    none,      /*     --indicator-style=none */
    slash,     /* -p, --indicator-style=slash */
    file_type, /*     --indicator-style=file-type */
    classify   /* -F, --indicator-style=classify */
};

enum sort_type
{
    sort_none = -1, /* -U */
    sort_name,      /* default */
    sort_extension, /* -X */
    sort_size,      /* -S */
    sort_version,   /* -v */
    sort_time,      /* -t */
    sort_numtypes   /* the number of elements of this enum */
};

