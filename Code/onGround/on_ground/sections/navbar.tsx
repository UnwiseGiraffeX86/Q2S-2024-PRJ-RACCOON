'use client';
import { Button } from "@/components/ui/button";
import React from "react";
import Image from "next/image";
import Logo from "../public/Logo.jpg"
import { Button2 } from "@/components/ui/button2";

export function Navbar() {
    return (
        // <nav className="flex justify-between  bg-primary text-primary-foreground p-4 ">

        //     <div className="text-lg font-bold">Logo</div>

        //     <div className="bg-secondary text-primary">
        //         Info
        //     </div>

        // </nav>
        <nav className="w-full p-4">
            <div className="container mx-auto flex justify-between items-center">
                <div className="text-lg text-primary-foreground font-bold">
                    Logo
                    {/* <Image
                        src={Logo}
                        alt='the logo'
                        height={50}
                        width={50}
                    /> */}
                </div>
                <div>
                    <Button variant={"secondary"} >
                        Info
                    </Button>
                </div>
            </div>
        </nav>


    );
}
