//
//  RugSlugApp.swift
//  Rug Slug App
//
//  Created by Kaixin Yu on 2/22/23.
//

import SwiftUI
import Foundation

////// ######### DECLARE VARIABLES ########
//var connected = true // FIX ME!!!!: INPUT FILE
//var battery = true // FIX ME: needs to be replaced to be an input from a file
//var waste = true // FIX ME: needs to be replaced to be an input from a file
//var solution = true // FIX ME: needs to be replaced to be an input from a file

//// ######### INPUT TEST FILE BELOW ########
struct Sensor: Codable, Identifiable {
    enum CodingKeys: CodingKey {
        case connected // Microcontroller connection: T for connected and F for not connected
        case charging // Charging mode: T for charging and F for not charging
        case battery // Battery life: T for enough battery and F for not enough battery
        case waste // Waste tank: T for full and F for empty
        case solution // Solution tank: T for full and F for empty
        case cleaning // Cleaning status: T for not cleaning and F for cleaning
    }
    
    var id = UUID()
    var connected: Bool
    var charging: Bool
    var battery: Bool
    var waste: Bool
    var solution: Bool
    var cleaning: Bool
}

class ReadData: ObservableObject  {
    @Published var sensors = [Sensor]()
    
    init(){
        loadData()
    }
    
    func loadData()  {
        guard let url = Bundle.main.url(forResource: "sensorData", withExtension: "json")
        else {
            print("Json file not found")
            return
        }
        
        let data = try? Data(contentsOf: url)
        let sensors = try? JSONDecoder().decode([Sensor].self, from: data!)
        self.sensors = sensors!
        
    }
    
}
//// ######### INPUT TEST FILE ABOVE ########

// ######### WELCOME PAGE ########
struct WelcomePage: View {
    var body: some View {
        NavigationView {
            VStack{
                // Title Page
                Text("Welcome to the Rug Slug App!")
                    .font(.largeTitle)
                    .multilineTextAlignment(.center)
                    .padding(.bottom, 50.0)
                
                // Go to Connect Page
                NavigationLink(destination: ConnectPage()){
                    Text("Let's Get Started!")
                        .font(.title)
                }
            }
        }
    }
}

// ######### SELECT ROBOT PAGE ########
struct ConnectPage: View {
    @ObservedObject var datas = ReadData() // Read data from the input json file
    
    var body: some View {
        ForEach(datas.sensors) {sensors in
            // Edge Case: Connection already made vs Need connection
            if sensors.connected {
                NavigationLink(destination: {
                    // Edge Case: Under cleaning state vs not
                    if sensors.cleaning {
                        CleaningPage()
                    } else {
                        HomePage()
                    }
                } ){
                    Text("Already connected to your Rug Slug Bot!")
                        .font(.largeTitle)
                }.navigationBarBackButtonHidden(true)
            } else {
                VStack{
                    NavigationLink(destination: {
                        if sensors.connected {
                            HomePage()
                        }
                        else {
                            FailedConnectPage()
                        }
                    } ){
                        Text("Connect to your Rug Slug Bot!")
                            .font(.largeTitle)
                    }.navigationBarBackButtonHidden(true)
                }
            }
        }
    }
}

// ######### FAILED CONNECTION PAGE ########
struct FailedConnectPage: View {
    var body: some View {
        VStack{
            NavigationLink(destination:
                            ConnectPage()){
                Text("Failed to connect, try again!")
                    .font(.largeTitle)
            }.navigationBarBackButtonHidden(true)
        }
    }
}

// ######### HOME PAGE ########
struct HomePage: View {
    @ObservedObject var datas = ReadData() // Read data from the input json file
    
    var body: some View {
        ForEach(datas.sensors) {sensors in
            VStack{
                // Edge Case: Lost connection vs Still connected
                if sensors.connected == false {
                    NavigationLink(destination: {
                        ConnectPage()
                    } ){
                        Text("Lost Connection to your Rug Slug Bot!")
                            .font(.largeTitle)
                    }.navigationBarBackButtonHidden(true)
                } else {
                    VStack{
                        // Title Page
                        Text("Home Page")
                            .font(.largeTitle)
                            .multilineTextAlignment(.center)
                            .padding(.bottom, 50.0)
                        
                        NavigationLink(destination: {
                            CleaningPage()
                        }){
                            Text("Start Cleaning")
                                .font(.title)
                                .padding(.bottom, 10.0)
                        }.navigationBarBackButtonHidden(true)
                        
                        NavigationLink(destination:
                                        ManualPage()){
                            Text("Manual")
                                .font(.title)
                        }.navigationBarBackButtonHidden(true)
                    }
                }
            }
        }
    }
}

// ######### CLEANING PAGE ########
struct CleaningPage: View {
    @ObservedObject var datas = ReadData() // Read data from the input json file
    
    var body: some View {
        ForEach(datas.sensors) {sensors in
            VStack{
                // Title Page
                Text("Cleaning Page")
                    .font(.largeTitle)
                    .multilineTextAlignment(.center)
                    .padding(.bottom, 50.0)
                HStack {
                    Text("Battery Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.battery == true) {
                        Text("Needs Charging")
                            .padding(.trailing)
                    } else {
                        Text("Charged Enough")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                //            THIS IS FOR WASTE TANK:
                //            FIX ME: ADD INPUT TO THE STATUS
                HStack {
                    Text("Waste Tank Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.waste == true) {
                        Text("Full")
                            .padding(.trailing)
                    } else {
                        Text("Empty")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                //            THIS IS FOR CHARGING STATION SOLUTION TANK:
                //            FIX ME: ADD INPUT TO THE STATUS
                HStack {
                    Text("Solution Tank Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.solution == true) {
                        Text("Full")
                            .padding(.trailing)
                    } else {
                        Text("Empty")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                NavigationLink(destination:
                                PausePage()){
                    Text("Pause")
                        .font(.largeTitle)
                }.navigationBarBackButtonHidden(true)
                
            }
        }
        
    }
}

// ######### PAUSE CLEANING PAGE ########
struct PausePage: View {
    @ObservedObject var datas = ReadData() // Read data from the input json file
    
    var body: some View {
        ForEach(datas.sensors) {sensors in
            VStack{
                // Title Page
                Text("Paused Cleaning Page")
                    .font(.largeTitle)
                    .multilineTextAlignment(.center)
                    .padding(.bottom, 50.0)
                HStack {
                    Text("Battery Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.battery == true) {
                        Text("Needs Charging")
                            .padding(.trailing)
                    } else {
                        Text("Charged Enough")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                //            THIS IS FOR WASTE TANK:
                HStack {
                    Text("Waste Tank Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.waste == true) {
                        Text("Full")
                            .padding(.trailing)
                    } else {
                        Text("Empty")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                //            THIS IS FOR CHARGING STATION SOLUTION TANK:
                //            FIX ME: ADD INPUT TO THE STATUS
                HStack {
                    Text("Solution Tank Status: ")
                        .font(.title2)
                        .multilineTextAlignment(.leading)
                        .padding(.leading)
                    Spacer()
                    if (sensors.solution == true) {
                        Text("Full")
                            .padding(.trailing)
                    } else {
                        Text("Empty")
                            .padding(.trailing)
                    }
                }
                .padding(.bottom)
                
                NavigationLink(destination:
                                HomePage()){
                    Text("Send to Charging Station")
                        .font(.largeTitle)
                        .padding(.bottom, 10.0)
                }.navigationBarBackButtonHidden(true)
                
                NavigationLink(destination:
                                CleaningPage()){
                    Text("Continue Cleaning")
                        .font(.largeTitle)
                }.navigationBarBackButtonHidden(true)
                
                
            }
        }
    }
}


// ######### MANUAL PAGE ########
struct ManualPage: View {
    var body: some View {
        VStack{
            // Title Page
            Text("Manual Page")
                .font(.largeTitle)
                .multilineTextAlignment(.center)
                .padding(.bottom, 50.0)
        }
    }
}

// ######### REPORT ISSUE PAGE ########
struct IssuePage: View {
    var body: some View {
        VStack{
            // Title Page
            Text("Report Issue Page")
                .font(.largeTitle)
                .multilineTextAlignment(.center)
                .padding(.bottom, 50.0)
        }
    }
}

struct Main_Previews: PreviewProvider {
    static var previews: some View {
        WelcomePage()
//        TestingPage()
    }
}
