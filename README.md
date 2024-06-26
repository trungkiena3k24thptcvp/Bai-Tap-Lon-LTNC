# BRAVE_SOLDIER - 23021589 Nguyễn Trung Kiên Edition
## Giới Thiệu:
 Game thuộc thể loại bắn súng. Hãy cùng nhập vai nhân vật và chiến đấu với quái vật để bảo vệ thế giới.
 - [1. Bắt đầu game](#1-bắt-đầu-game)
 - [2. Các thành phần](#2-các-thành-phần)
 - [a. Nhân vật game:](#a-nhân-vật-game)
 - [b. Quái vật:](#b-quái-vật)
 - [c. Hướng dẫn:](#c-hướng-dẫn)
 - [3. Về source code của game](#3-về-source-code-của-game)
 - [4. Tài liệu tham khảo](#4-tài-liệu-tham-khảo)
 - [5. Một số bug chưa fix được](#5-một-số-bug-chưa-fix-được)
## 1. Bắt đầu game
 - Màn hình Load Game:
   ![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/ce82dbd5-a5cc-44b1-b68e-ce0bd3746e03)
 - Menu:
   ![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/2efd4057-0120-48eb-abf9-2090cda1fc2c)
   + Nhấn nút Play Game để bắt đầu chơi.
   + Nhấn nút Help để hướng dẫn các chức năng của game.
    ![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/43b1068b-0681-4399-be72-90f92e370e97)
   + Nhấn nút Exit để thoát game.
## 2. Các thành phần
## a. Nhân vật game:
 - Ban đầu bạn sẽ có 2 mạng và khi số mạng giảm về 0 bạn sẽ GAME OVER.
 - Vũ khí là súng và sẽ bắn ra đạn để tiêu diệt quái vật.
   ![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/3f980a60-a02f-4373-856e-fd33bc912a33)
 - Mỗi khi chạm vào hình trái tim ở trên bản đồ, bạn sẽ được cộng thêm 1 mạng.
   ![19](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/4f4fe8ce-5eb6-46df-917b-96360a4c5144)
 - Mỗi khi chạm vào đồng tiền, số tiền của bạn sẽ tăng lên.
   ![4](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/a2467616-28ce-4f5e-ac00-33577af2ad77)
 - Bạn sẽ nhận được thêm loại đạn mới chạm vào biểu tượng đạn.
   ![18](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/0ed628b0-fd08-4000-96a7-0d7f24bd9aef)
## b. Quái vật:
 - Quái vật đứng yên và bắn ra loại đạn trong 1 khoảng nhất định.
![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/dc421f6c-f2e8-4fdf-b95b-82903dd01934)
 - Quái vật động di chuyển trong một khoảng nhất định.
![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/c73834c5-eff5-421d-adbb-fbd100de3090)
 - Quái vật bay trên trời.
![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/db22131a-dd8d-444f-97c5-f90b23f80a7e)
 - Boss là một con rồng ngàn tuổi khổng lồ
![image](https://github.com/trungkiena3k24thptcvp/Bai-Tap-Lon-LTNC/assets/162546220/4c4eb677-c654-4836-8b3b-b44eaef4bbde)
## c. Hướng dẫn:
 - Để di chuyển nhân vật ta nhấn các phím hướng để di chuyển theo các hướng ta mong muốn.
 - Nhấn phím 1 để bắn đạn.
 - Khi ta có 2 loại đạn: nhấn F để bắn đạn đỏ và G để bắn đạn xanh.
 - Khi ta chạm vào quái vật hoặc trúng đạn hay bị rơi xuống vực ta sẽ bị mất 1 mạng.
 - Ta sẽ bất tử khoảng 1s sau khi hồi sinh.
 - Khi hồi sinh nhân vật sẽ rơi từ trên trời xuống trước cách vị trí mà ta mất mạng.
 - Nhấn phím Enter để bật/tắt âm thanh.
## 3. Về source code của game
 - File CommonFunction.cpp và CommonFunction.h để chứa các hàm thông dụng, cơ bản nhất của game và các thông số.
 - File GameMap.cpp và GameMap.h để tạo ra và hiển thị các map lên màn hình.
 - File BaseObject.cpp và BaseObject.h để hiển thị các sự vật, background lên màn hình.
 - File Character.cpp và Character.h để thiết lập các chức năng của nhân vật như di chuyển, bắn đạn, hiển thị, ...
 - File PlayerPower.cpp và PlayerPower.h để kiểm soát các thông số của nhân vật.
 - File PlayerMoney.cpp và PlayerMoney.h để kiểm soát tiền mà nhân vật kiếm được.
 - File Explosion.cpp và Explosion.h để thiết lập các vụ nổ khi bắn trúng quái vật hoặc khi nhân vật bị bắn hay chạm vào quái vật.
 - File BulletObject.cpp và BulletObject.h để thiết lập đạn cho các nhân vật hay quái vật.
 - File ThreatObject.cpp và ThreatObject.h để thiết lập các thông số cho quái vật.
 - File BossObject.cpp và BossObject.h để kiểm soát thông số của Boss.
 - Và một vài file khác (Tải source code để biết thêm chi tiết).
## 4. Tài liệu tham khảo 
 - Lazyfoo
 - Youtube
## 5. Một vài bug chưa fix được
 - Quái vật bị mắc kẹt
 - Đạn 1 số quái vật bị bắn ra sau đầu
 - Chưa add thêm các map type.








   
