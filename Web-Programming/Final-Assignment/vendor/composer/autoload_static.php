<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInitbb537988b293ef15c769ea0b40aa2534
{
    public static $prefixLengthsPsr4 = array (
        'A' => 
        array (
            'App\\' => 4,
        ),
    );

    public static $prefixDirsPsr4 = array (
        'App\\' => 
        array (
            0 => __DIR__ . '/../..' . '/App',
        ),
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixLengthsPsr4 = ComposerStaticInitbb537988b293ef15c769ea0b40aa2534::$prefixLengthsPsr4;
            $loader->prefixDirsPsr4 = ComposerStaticInitbb537988b293ef15c769ea0b40aa2534::$prefixDirsPsr4;

        }, null, ClassLoader::class);
    }
}