//////
//////  Testing.swift
//////  Rug Slug App
//////
//////  Created by Kaixin Yu on 2/22/23.
//////
////
////import SwiftUI
////
////struct Screen2: View {
//////    @Binding var showWelcome: Bool
////
////    var body: some View {
//////        showWelcome = false
////        Text("hello")
////    }
////}
////
////struct Main: View {
//////    @State private var showWelcome = true
////
////    var body: some View {
////        VStack {
//////            if showWelcome {
//////                Text("Welcome!")
//////                    .font(.largeTitle)
//////                    .fontWeight(.bold)
//////                    .padding(.top)
//////
//////                Text("You are about to start using the best robot ever!")
//////                    .font(.title2)
//////                    .multilineTextAlignment(.center)
//////                    .padding(.vertical)
//////
//////                Text("The Rug Slug!")
//////                    .font(.title)
//////                    .fontWeight(.semibold)
//////                    .multilineTextAlignment(.center)
//////                    .padding(.bottom)
//////            }
////
////            NavigationView{
////                List {
////                    NavigationLink(destination: Screen2(), label: {Text("Let's Get Started!")
////                            .fontWeight(.semibold)
////                        .multilineTextAlignment(.center)})
////
////                }
////                .navigationBarBackButtonHidden(true)
////            }
////
////        }
////    }
////}
////
////struct Main_Previews: PreviewProvider {
////    static var previews: some View {
////        Main()
////    }
////}
////import SwiftUI
////
////struct PageOne: View {
////    var body: some View {
////        NavigationView {
////            VStack{
////                NavigationLink(destination: PageTwo()){
////                    Text("Go to Page Two")
////                }
////            }
////        }
////    }
////}
////
////// Hide from page 2 -> page 1
////struct PageTwo: View {
////    var body: some View {
////        VStack{
////            NavigationLink(destination: PageThree()){
////                Text("Go to Page Three")
////            }.navigationBarBackButtonHidden(true)
////        }
////    }
////}
////
//////// Hide from page 3 -> page 2 (Same behaviour as Kheldar's answer above)
//////struct PageTwo: View {
//////    var body: some View {
//////        VStack{
//////            NavigationLink(destination: PageThree().navigationBarBackButtonHidden(true)){
//////                Text("Go to Page Three")
//////            }
//////        }
//////    }
//////}
////
////
////struct PageThree: View {
////    var body: some View {
////        Text("Hello!")
////    }
////}
////
////struct Main_Previews: PreviewProvider {
////    static var previews: some View {
////        PageOne()
////    }
////}
//import SwiftUI
//import Foundation
//
////// ######### INPUT TEST FILE BELOW ########
//struct SensorTesting: Codable, Identifiable {
//    enum CodingKeys: CodingKey {
//        case connected
//        case battery
//        case waste
//        case solution
//    }
//
//    var id = UUID()
//    var connected: Bool
//    var battery: Bool
//    var waste: Bool
//    var solution: Bool
//}
//
//class ReadDataTesting: ObservableObject  {
//    @Published var sensors = [Sensor]()
//
//    init(){
//        loadData()
//    }
//
//    func loadData()  {
//        guard let url = Bundle.main.url(forResource: "sensorData", withExtension: "json")
//        else {
//            print("Json file not found")
//            return
//        }
//
//        let data = try? Data(contentsOf: url)
//        let sensors = try? JSONDecoder().decode([Sensor].self, from: data!)
//        self.sensors = sensors!
//
//    }
//
//}
//
//func editTest() {
//    let json = CkoJsonObject()
//
//    // Load the JSON from a file.
//    var success: Bool = json.LoadFile("qa_data/json/modifySample.json")
//    if success != true {
//        print("Json file not found 2")
//        return
//    }
//
//// ######### WELCOME PAGE ########
//struct TestingPage: View {
//    @ObservedObject var datas = ReadData()
//
//    var body: some View {
////        List(datas.sensors) { sensors in
//        ForEach(datas.sensors) {sensors in
//            VStack{
//                // Title Page
//                Text("Testing")
//                    .font(.largeTitle)
//                    .multilineTextAlignment(.center)
//                    .padding(.bottom, 50.0)
//                if sensors.connected == true {
//                    Text("Connected")
//                    // FIX ME
//                } else {
//                    Text("NOT Connected")
//                }
//                if sensors.battery == true {
//                    Text("Full Charged")
//                } else {
//                    Text("Needs Charging")
//                }
//                if sensors.waste == true {
//                    Text("Waste Tank Full")
//                } else {
//                    Text("Waste Tank Ready")
//                }
//                if sensors.solution == true {
//                    Text("Solution Tank Ready")
//                } else {
//                    Text("Solution Tank Empty")
//                }
//
//            }
//        }
//    }
//}
//// ######### INPUT TEST FILE ABOVE ########
//
//struct Previews_Testing_Previews: PreviewProvider {
//    static var previews: some View {
//        TestingPage()
//    }
//}
