import { Card, CardTitle } from "@/components/ui/card";
import { Navbar } from "@/sections/navbar";
import Image from "next/image";

export default function Home() {
  return (
    <div className="flex flex-col h-screen">
      <div className="h-[10%] w-full flex justify-between bg-primary">
        <Navbar />
      </div>



      <div className="h-[90%] bg-secondary flex items-center justify-center">
        <Card >
          <CardTitle className="p-10 flex">
            Conect your PoketQube
          </CardTitle>
        </Card>
      </div>





    </div>



    // <div className="flex items-center justify-center h-screen">
    //   <Navbar />
    //   <div className="bg-card p-4 rounded-lg">
    //     <Card>
    //       <CardTitle className="p-10">
    //         Conect your PoketQube
    //       </CardTitle>
    //     </Card>
    //   </div>
    // </div>

  );
}
