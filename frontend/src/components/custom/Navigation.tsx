import {
    NavigationMenu,
    NavigationMenuContent,
    NavigationMenuItem,
    NavigationMenuLink,
    NavigationMenuList,
    NavigationMenuTrigger,
  } from "@/components/ui/navigation-menu";

import '../components.css';

function Nav() {
  return (
    <nav className="navbar">
        <NavigationMenu>
            {/* <img src="/img.png" className = "logo" alt="Logo" /> */}
            <NavigationMenuList>
                <NavigationMenuItem>
                    <NavigationMenuTrigger className={"item"}>Signup</NavigationMenuTrigger>
                    <NavigationMenuContent >
                    <NavigationMenuLink>Signup</NavigationMenuLink>
                    </NavigationMenuContent>
                </NavigationMenuItem>
            </NavigationMenuList>
        </NavigationMenu>
  </nav>
  )
}
export default Nav;